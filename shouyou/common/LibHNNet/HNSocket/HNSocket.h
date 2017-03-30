/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __NH_HNSocket_H__
#define __NH_HNSocket_H__

#if defined (WIN32) || defined (_WIN32)
	//#include <winsock2.h>
#include<WS2tcpip.h>
	typedef int socklen_t;
	#define ioctl ioctlsocket
	#define Errno GetLastError()
	enum
	{
		SHUT_RD = 0,
#define SHUT_RD			SHUT_RD
		SHUT_WR,
#define SHUT_WR			SHUT_WR
		SHUT_RDWR
#define SHUT_RDWR		SHUT_RDWR
	};
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
    #include <unistd.h>
	#include <sys/ioctl.h>
	#include <fcntl.h>
	typedef int SOCKET;
	#define INVALID_SOCKET		-1
	#define SOCKET_ERROR		-1
	#define BLOCKREADWRITE      MSG_WAITALL  
	#define NONBLOCKREADWRITE   MSG_DONTWAIT  
	#define SENDNOSIGNAL        MSG_NOSIGNAL  
	#define Errno errno
#endif

#include <vector>
#include <string>
#include "cocos2d.h"

namespace HN 
{

const char *strError(int x) ;
void initSocket();
class HNSocket
{
public:
	enum Status
	{
		TCP_CONNECT_OUTTIME	 = -1,
		TCP_CONNECT_ERROR	 = -2,
        TCP_CONNECT_SUCCESS	 = 0
	};

public:
	static bool isValidIP(const std::string& host);
	static std::vector<std::string> getIpAddress(const char *host);
    static int getIpVersion(const std::string& ip);

public:
	HNSocket(void);
	virtual ~HNSocket(void);

public:
	bool create();
	int connect();
	int connect(const char* ip, int port);
	int connectWithHost(const char* host, int port);
	int send(const char* data, int dataSize);
	int recv(char* buffer, int size);
	bool close();
	int select(timeval* timeOut);
	int isConnected();

public:
	bool setNonblocking(bool bNb);
	bool setSoRcvtimeo(struct timeval& tv);
	bool setSoSndtimeo(struct timeval& tv);
	bool setSoRcvbuf(int x);
	bool soRcvbuf();
	bool setSoSendbuf(int x);
	bool soSendbuf();
	unsigned short getSockPort();

public:
    void setIp(const std::string& ip);
	inline std::string getIp() const  { return _ip; }

	inline void setHost(const std::string& host) { _host = host; }
	inline std::string getHost() const  { return _host; }

	inline void setPort(int port) { _port = port; }
	inline int getPort() const { return _port; }

protected:
    // ip协议簇
    int _ai_family;
private:
	bool shutdown();

private:
	std::vector<std::string> _ips;
	int _port;
	std::string _host;
	std::string _ip;
	SOCKET _socket;
};

};

#endif	//__NH_HNSocket_H__
