/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNSocketThread.h"
#include "HNSocket.h"
#include "HNSocketMessage.h"
#include "HNSocketProtocolData.h"
#include "HNSocketEventDelegate.h"
#include "HNCommon/HNLog.h"
#include "HNCommon/HNCommonMarco.h"

namespace HN
{
	static const INT TCP_BUFSIZE_READ = 8192;
	static const INT TCP_RECV_BUFFER_SIZE = 100*1024;
	static const INT TCP_SEND_BUFFER_SIZE = 16400;

	HNSocketThread::HNSocketThread(ISocketEventDelegate* delegate) 
		: _recvThreadExit(true)
		, _heartBeatThreadExit(true)
		, _connected(false)
		, _delegate(delegate)
	{
		_socket = new HNSocket();
		_socketDataCacheQueue = new HNSocketDataCacheQueue();	
		_socketMessageQueue = new HNSocketMessageQueue();
	}

	HNSocketThread::~HNSocketThread(void)
	{
		close();

		clearMessageCache();

		HN_SAFE_DELETE(_socketMessageQueue);
		HN_SAFE_DELETE(_socketDataCacheQueue);
		HN_SAFE_DELETE(_socket);
	}

	bool HNSocketThread::openWithIp(const CHAR* ip, INT port)
	{
		assert(ip != nullptr);
		if (!_connected)
		{
			_socket->setIp(ip);
			_socket->setPort(port);
			std::thread recvThread(std::bind(&HNSocketThread::onSocketReadThread, this));
			recvThread.detach();
		}
		return true;
	}

	bool HNSocketThread::openWithHost(const CHAR* host, INT port)
	{
		assert(host != nullptr);
		if (!_connected)
		{
			_socket->setHost(host);
			_socket->setPort(port);
			std::thread recvThread(std::bind(&HNSocketThread::onSocketReadThread, this));
			recvThread.detach();
		}
		return true;
	}

	bool HNSocketThread::initSocket()
	{
		bool ret = false;
		do
		{
			// create socket
			if (!_socket->create()) break;

			// set recv buffer
			_socket->setSoRcvbuf(TCP_RECV_BUFFER_SIZE);

			// set send buffer
			_socket->setSoSendbuf(TCP_SEND_BUFFER_SIZE);

			INT err = _socket->connect();

			if (HNSocket::TCP_CONNECT_SUCCESS == err)
			{
				_connected = true;
				_recvThreadExit = false;
				ret = true;
			}
			else
			{
				HNSocketMessage* SocketMessage = HNSocketMessage::getMessage();
				SocketMessage->socketStatus = SocketStatus_ERROR;
				{
					std::lock_guard <std::mutex> autoLock(_dataMutex);
					_socketMessageQueue->push_back(SocketMessage);
				}
				_delegate->onReadComplete();
			}
		} while (0);

		return ret;
	}

	void HNSocketThread::clear()
	{
		_connected = false;
		_recvThreadExit = true;
		_heartBeatThreadExit = true;
		_socketDataCacheQueue->clear();
	}

	bool HNSocketThread::close()
	{
		if (_connected)
		{
			log("%s >> onSocketReadThread >> close.", _tag.c_str());
			clear();
			_socket->close();
			return true;
		}
		return false;
	}

	INT HNSocketThread::send(char* object, INT objectSize)
	{
		if (_connected)
		{
			return _socket->send(object, objectSize);
		}
		HNLOG_ERROR ("error: network not connected");
		return -1;
	}

	void HNSocketThread::onSocketReadThread()
	{
		if (!initSocket()) return;

		HNLOG_ERROR ("%s >> onSocketReadThread >> begin.", _tag.c_str());
		
		while (true)
		{
			if (_recvThreadExit) break;

			timeval timeOut = {16, 0}; 
			INT nready = _socket->select(&timeOut);

			// outtime
			if (nready == 0)
			{
				// ios用超时进行断网判断，安卓用心跳检测进行判断
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				HNLOG_ERROR("%s >> outtime >> %s >> (%d)", _tag.c_str(), strerror(errno), nready);
				disconnectMsgNotify();
				break;
#else
				continue;
#endif
			}

			// network error
			if (nready < 0)
			{
				HNLOG_ERROR("%s >> network error >> %s >> (%d)", _tag.c_str(), strerror(errno), nready);
				disconnectMsgNotify();
				break;
			}
        
			CHAR readBuffer[TCP_BUFSIZE_READ];
			INT recvSize = _socket->recv(readBuffer, sizeof(readBuffer));
        
			if (recvSize > 0)
			{
				onRead(readBuffer, recvSize);
			}
			
			// 0: server close / -1: network error
			if (recvSize <= 0)
			{
				if (errno != EWOULDBLOCK && errno != EINTR) {
					HNLOG_ERROR("%s >> network error >> %s >> (%d)", _tag.c_str(), strerror(errno), recvSize);
					disconnectMsgNotify();
					break;
				}
			}
		}
	
		HNLOG_ERROR ("%s >> onSocketReadThread >> end.", _tag.c_str());
	}

	void HNSocketThread::onRead(CHAR* buffer, INT recvSize)
	{
		// 参数校验
		if (!buffer || 0 >= recvSize) return;

		// cache network data
		_socketDataCacheQueue->push(buffer, recvSize);

		const UINT NetMessageHeadSize = sizeof(NetMessageHead);

		NetMessageHead* pMessageHead = nullptr;
	
		UINT messageSize = (UINT)_socketDataCacheQueue->size();
		if (messageSize >= NetMessageHeadSize)
		{
			do
			{
				pMessageHead = (NetMessageHead*) _socketDataCacheQueue->front();
				if (nullptr != pMessageHead && messageSize >= pMessageHead->uMessageSize)
				{
					CHAR* pData = _socketDataCacheQueue->front() + NetMessageHeadSize;
					HNSocketMessage* SocketMessage = HNSocketMessage::getMessage();
					if (SocketMessage)
					{
						SocketMessage->setMessage(pMessageHead, pData, pMessageHead->uMessageSize - NetMessageHeadSize);
						SocketMessage->socketStatus = SocketStatus_RECV;
						_socketDataCacheQueue->pop(pMessageHead->uMessageSize);

						if(MDM_CONNECT == SocketMessage->messageHead.bMainID && ASS_NET_TEST_1 == SocketMessage->messageHead.bAssistantID)
						{						
							if (_heartBeatThreadExit)
							{
								_heartBeatThreadExit = false;
								// create heartBeat Thread
								std::thread heartBeatThread(std::bind(&HNSocketThread::onHeartBeatThread, this));
								heartBeatThread.detach();
							}
							HNSocketMessage::releaseMessage(SocketMessage);
						}
						else
						{
							bool bBackground = Configuration::getInstance()->getValue("bBackground", Value(false)).asBool();
							bool bControl = Configuration::getInstance()->getValue("bControl", Value(false)).asBool();

							std::lock_guard <std::mutex> autoLock(_dataMutex);
							if (bControl && bBackground)
							{
								if (SocketMessage->messageHead.bMainID != MDM_GM_GAME_NOTIFY)
								{
									_socketMessageQueue->push_back(SocketMessage);
									_delegate->onReadComplete();
								}
								else
								{
									HNSocketMessage::releaseMessage(SocketMessage);
								}
							}
							else
							{
								_socketMessageQueue->push_back(SocketMessage);
								_delegate->onReadComplete();
							}
						}						
					}
					else
					{
						clearMessageCache();

						disconnectMsgNotify();
						break;
					}
				}
				else
				{
					HNLOG_WARNING("%s >> not a complete data packet [messageSize = %lu, pMessageHead->uMessageSize = %lu]",
						_tag.c_str(), messageSize, pMessageHead->uMessageSize);
				}
				messageSize = (UINT)_socketDataCacheQueue->size();
				//HNLOG_INFO("%s >> messageSize ---> end = [%lu]", _tag.c_str(), messageSize);
			} while(messageSize >= pMessageHead->uMessageSize);
		}
	}

	void HNSocketThread::transform(std::function<void(HNSocketMessage* socketMessage)> func)
	{
		int queueSize = 0;
		do 
		{	
			HNSocketMessage* socketMessage = nullptr;
			{
				std::lock_guard < std::mutex > autoLock(_dataMutex);
				queueSize = _socketMessageQueue->size();
				if (queueSize > 0)
				{
					socketMessage = _socketMessageQueue->front();
					_socketMessageQueue->pop_front();
				}
			}
			if (nullptr != socketMessage)
			{
				func(socketMessage);
				HNSocketMessage::releaseMessage(socketMessage);
			}
		} while (queueSize > 0);
		Director::getInstance()->getScheduler()->pauseTarget(this);
	}

	void HNSocketThread::onHeartBeatThread()
	{
		while (true)
		{
			if (_heartBeatThreadExit) break;
			heartBeat();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			Sleep(5000);
#else
			sleep(5);
#endif
		}
	}

	void HNSocketThread::heartBeat()
	{
		if (_tag.compare("platform") == 0 && INVALID_VALUE != HNSocketProtocolData::PlatformCheckCode)
		{
			HNSocketProtocolData data;
			data.createPackage(MDM_CONNECT, ASS_NET_TEST_1, HNSocketProtocolData::PlatformCheckCode);
			send(data.getPackage(), data.getPackageSize());
		}
		else if (_tag.compare("game") == 0 && INVALID_VALUE != HNSocketProtocolData::GameCheckCode)
		{
			HNSocketProtocolData data;
			data.createPackage(MDM_CONNECT, ASS_NET_TEST_1, HNSocketProtocolData::GameCheckCode);
			send(data.getPackage(), data.getPackageSize());
		}
	}

	void HNSocketThread::disconnectMsgNotify()
	{
		if (_recvThreadExit) return;

		HNSocketMessage* SocketMessage = HNSocketMessage::getMessage();
		SocketMessage->socketStatus = SocketStatus_DISCONNECT;
		{
			std::lock_guard <std::mutex> autoLock(_dataMutex);
			_socketMessageQueue->push_back(SocketMessage);
		}
		_delegate->onReadComplete();
		close();
	}

	void HNSocketThread::clearMessageCache()
	{
		std::lock_guard <std::mutex> autoLock(_dataMutex);
		for (auto iter = _socketMessageQueue->begin(); iter != _socketMessageQueue->end();)
		{
			HNSocketMessage* message = *iter;
			HNSocketMessage::releaseMessage(message);
			iter = _socketMessageQueue->erase(iter);
		}
		_socketMessageQueue->clear();
	}
}
