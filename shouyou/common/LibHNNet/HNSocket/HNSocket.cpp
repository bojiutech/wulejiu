/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNSocket.h"
#include <errno.h>
#include "HNCommon/HNLog.h"
//#include <assert.h>

namespace HN
{
#if defined(_WIN32) || defined(WIN32)
	bool shasInit = false;
#endif

    const char *strError(int x)
    {
        static	char tmp[100];
        switch (x)
        {
        case 10004: return "Interrupted function call.";
        case 10013: return "Permission denied.";
        case 10014: return "Bad address.";
        case 10022: return "Invalid argument.";
        case 10024: return "Too many open files.";
        case 10035: return "Resource temporarily unavailable.";
        case 10036: return "Operation now in progress.";
        case 10037: return "Operation already in progress.";
        case 10038: return "Socket operation on nonsocket.";
        case 10039: return "Destination address required.";
        case 10040: return "Message too long.";
        case 10041: return "Protocol wrong type for socket.";
        case 10042: return "Bad protocol option.";
        case 10043: return "Protocol not supported.";
        case 10044: return "Socket type not supported.";
        case 10045: return "Operation not supported.";
        case 10046: return "Protocol family not supported.";
        case 10047: return "Address family not supported by protocol family.";
        case 10048: return "Address already in use.";
        case 10049: return "Cannot assign requested address.";
        case 10050: return "Network is down.";
        case 10051: return "Network is unreachable.";
        case 10052: return "Network dropped connection on reset.";
        case 10053: return "Software caused connection abort.";
        case 10054: return "Connection reset by peer.";
        case 10055: return "No buffer space available.";
        case 10056: return "Socket is already connected.";
        case 10057: return "Socket is not connected.";
        case 10058: return "Cannot send after socket shutdown.";
        case 10060: return "Connection timed out.";
        case 10061: return "Connection refused.";
        case 10064: return "Host is down.";
        case 10065: return "No route to host.";
        case 10067: return "Too many processes.";
        case 10091: return "Network subsystem is unavailable.";
        case 10092: return "Winsock.dll version out of range.";
        case 10093: return "Successful WSAStartup not yet performed.";
        case 10101: return "Graceful shutdown in progress.";
        case 10109: return "Class type not found.";
        case 11001: return "Host not found.";
        case 11002: return "Nonauthoritative host not found.";
        case 11003: return "This is a nonrecoverable error.";
        case 11004: return "Valid name, no data record of requested type.";

        default:
            break;
        }
        sprintf(tmp, "Winsock error code: %d", x);
        return tmp;
    }

    void initSocket()
    {
    #if defined(_WIN32) || defined(WIN32)

        //if (!shasInit)
        {
            do
            {
                WORD wVersionRequested = MAKEWORD(1, 1);
                WSADATA wsaData = {0};
                // WinSock init
                int ret = WSAStartup(wVersionRequested, &wsaData);
                if (ret != 0)
                {
                    printf("WSAStartup() failed!\n");
                    break;
                }
                // Confirm the WinSock DLL version 2.2
                if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
                {
                    WSACleanup();
                    printf("Invalid WinSock version!\n");
                    break;
                }
                printf("WinSock init success!\n");
            } while (0);
            shasInit = true;
        }

    #endif
    }

    static void uninstallSocket()
    {
    #if defined(_WIN32) || defined(WIN32)
        WSACleanup(); 
    #endif
    }

    bool HNSocket::isValidIP(const std::string& host)
    {
		return false;
       // initSocket();
       // 
       //// bool bRet = (inet_addr(host.c_str()) != INADDR_NONE);
       // 
       // bool bRet = (inet_pton(AF_INET, host.c_str(), nullptr) == 1);
       // 
       // uninstallSocket();
       // return bRet;
    }

    std::vector<std::string> HNSocket::getIpAddress(const char *host) 
    {
        initSocket();
        
        std::vector<std::string> ips;
        
        struct addrinfo addr;
        struct addrinfo* pAddr = &addr;
        
        struct addrinfo hints;
		memset(&hints, 0x00, sizeof(hints));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_IP;
        
        int nRet = getaddrinfo(host, nullptr, &hints, &pAddr);
        
        do
        {
            // 信息获取失败
            if(nRet != 0)
                break;
            
            // ipv4
            if(pAddr->ai_family == AF_INET)
            {
                struct sockaddr_in* ipv4 = nullptr;
                char str[16] = {0};
                for(auto iter = pAddr; iter != nullptr; iter = iter->ai_next)
                {
                    ipv4 = (struct sockaddr_in*)iter->ai_addr;
                    inet_ntop(AF_INET, &ipv4->sin_addr, str, 32);
                    ips.push_back(str);
                }
            }
            
            // ipv6
            else if(pAddr->ai_family == AF_INET6)
            {
                struct sockaddr_in6* ipv6 = nullptr;
                char str[40] = {0};
                for(auto iter = pAddr; iter != nullptr; iter = iter->ai_next)
                {
                    ipv6 = (struct sockaddr_in6*)iter->ai_addr;
                    inet_ntop(AF_INET6, &ipv6->sin6_addr, str, 32);
                    ips.push_back(str);
                }
            }
            else
                break;
        }while(0);
        
        uninstallSocket();
        return ips;
    }
    
    int HNSocket::getIpVersion(const std::string& ip)
    {
        return 0;
    }

    HNSocket::HNSocket(void)
        :_socket(INVALID_SOCKET)
        , _port(-1)
        ,_ai_family(AF_UNSPEC)
    {
        initSocket();
    }

    HNSocket::~HNSocket(void)
    {
        close();
        uninstallSocket();
    }

    bool HNSocket::create()
    {
        _socket = INVALID_SOCKET;
        bool ret = false;
        do
        {
            _socket = socket(_ai_family, SOCK_STREAM, 0);
            if (INVALID_SOCKET == _socket)
            {
                printf("socket create: %s", strerror(errno));
                close();
                break;
            }
            ret = true;
        } while (0);

        return ret;
    }

    int HNSocket::connect()
    {
        return connect(_ip.c_str(), _port);
    }

    int HNSocket::connectWithHost(const char* host, int port)
    {
        int ret = -1;
        do 
        {
            _ips = getIpAddress(host);
            for (auto iter = _ips.begin(); iter != _ips.end(); ++iter)
            {
                ret = connect(iter->c_str(), port);
                if (0 == ret)
                {
                    break;
                }
            }
        } while (0);
        return ret;
    }

    int HNSocket::connect(const char* ip, int port)
    {
        assert(nullptr != ip);
        assert(port >= 0);
        
        int nready = 0;

        this->_ip = ip;
        this->_port = port;
        
        if(_ai_family == AF_INET6)
        {
            sockaddr_in6 sa = {0};
            struct in6_addr addr = {0};
            int nRet = inet_pton(_ai_family, this->_ip.c_str(), (void*)&addr);
            
            sa.sin6_family = _ai_family;
            sa.sin6_port = htons(this->_port);
            sa.sin6_addr = addr;
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            int set = 1;
            setsockopt(_socket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
#endif
            
            // set to a non blocking mode
            setNonblocking(true);
            
            nready = ::connect(_socket, (sockaddr*)&sa, sizeof(sa));
        }
        else
        {
            sockaddr_in sa = {0};
            struct in_addr addr = {0};
            int nRet = inet_pton(_ai_family, this->_ip.c_str(), (void*)&addr);
            
            sa.sin_family = _ai_family;
            sa.sin_port = htons(this->_port);
            sa.sin_addr = addr;
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            int set = 1;
            setsockopt(_socket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
#endif
            
            // set to a non blocking mode
            setNonblocking(true);
            
            nready = ::connect(_socket, (sockaddr*)&sa, sizeof(sa));
        }        
        
        do
        {
            if (SOCKET_ERROR == nready)
            {
                int optval = -1;
                int optlen = sizeof(int);
                timeval tm = {10, 0};
                fd_set set = {0};
                FD_ZERO(&set);
                FD_SET(_socket, &set);
                nready = ::select(_socket + 1, nullptr, &set, nullptr, &tm);
                
                if (nready < 0)
                {
                    printf ("ret = %d >> 1", nready);
                    nready = TCP_CONNECT_ERROR; // network error
                    break;		
                }
                else if (nready == 0)
                {
                    printf ("ret = %d >> 2", nready);
                    nready = TCP_CONNECT_OUTTIME; // network outtime
                    break;
                }
                else if (nready > 0)
                {
                    int err = getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char*)&optval, (socklen_t*)&optlen);
                    if (0 != optval)
                    {
                        printf ("err = %d, error = %d << 3", err, optval);
                        nready = TCP_CONNECT_OUTTIME;	// network outtime
                        break;
                    }
                }
                nready = 0;
            }
        } while (0);
        
        // set for blocking mode
        setNonblocking(false);

        if (TCP_CONNECT_OUTTIME == nready)
        {
            printf ("connect network outtime: %s", strerror(errno));
            close();
        }

        if (TCP_CONNECT_ERROR == nready)
        {
            printf ("connect network error: %s", strerror(errno));
            close();
        }
        return nready;
    }

    int HNSocket::send(const char* data, int dataSize)
    {
        int bytes = 0;
        int count = 0;
        while (count < dataSize)
        {
            bytes = (int)::send(_socket, data + count, dataSize - count, 0);
            if (-1 == bytes || 0 == bytes)
            {
    #if defined(_WIN32) || defined(WIN32)
                if (Errno != WSAEWOULDBLOCK)
    #else
                if (Errno != EWOULDBLOCK)
    #endif
                {	
                    printf ("network send >> %d >> %s\n", Errno, strError(Errno));
                    close();
                }
                return -1;
            }
            count += bytes;
        }
        return count;
    }

    int HNSocket::recv(char* buffer, int size)
    {
        return (int)::recv(_socket, buffer, size, 0);
    }

    int HNSocket::select(timeval* timeOut)
    {
        fd_set readfd;
        FD_ZERO(&readfd);
        FD_SET(_socket, &readfd);
    /*
                EBADF  An invalid file descriptor was given in one of the sets.
                EINTR  A non blocked signal was caught.
                EINVAL n is negative. Or struct timeval contains bad time values (<0).
                ENOMEM select was unable to allocate memory for internal tables.
    */
        int nready = ::select(_socket + 1, &readfd, nullptr, nullptr, timeOut);

        if (nready < 0)
        {
            int nready = Errno;
    #if defined(_WIN32) || defined(WIN32)
            switch (nready)
            {
            case WSAENOTSOCK:
                break;
            case WSAEINTR:
            case WSAEINPROGRESS:
                break;
            case WSAEINVAL:
                printf ("select : %d >> %s", nready, strError(nready));
                break;
            case WSAEFAULT:
                printf ("select : %d >> %s", nready, strError(nready));
                break;
            case WSANOTINITIALISED:
                printf ("WSAStartup not successfully called");
                break;
            case WSAENETDOWN:
                printf ("Network subsystem failure");
                break;
            }
    #else
            switch (nready)
            {
            case EBADF:
                break;
            case EINTR:
                break;
            case EINVAL:
                printf ("select : %d >> %s", nready, strError(nready));
                break;
            case ENOMEM:
                printf ("select : %d >> %s", nready, strError(nready));
                break;
            }
    #endif
        }
        else if (0 == nready)
        {
            // outtime
        }
        else 
        {
        }
        return nready;
    }

    bool HNSocket::close()
    {
		shutdown();

        int ret = 0;
    #if defined(_WIN32) || defined(WIN32)
        ret = ::closesocket(_socket);
    #else
        ret = ::close(_socket);
    #endif
		/*if (ret == 0)
		{
		shutdown();
		}*/

		log("%d >> HNSocket >> shutdown.", ret);
        
		return ret == 0;
    }

    bool HNSocket::shutdown()
    {
        int ret = 0;	
		ret = ::shutdown(_socket, SHUT_RDWR);
        if (ret < 0)
        {
    #if defined(WIN32) || defined(_WIN32)
            int err = WSAGetLastError();
            switch (err)
            {
            case WSANOTINITIALISED://：在使用此API之前应首先成功地调用WSAStartup()。
                {

                } break;
            case WSAENETDOWN://：WINDOWS套接口实现检测到网络子系统失效。
                {

                } break;
            case WSAEINVAL://：how参数非法。
                {

                } break;
            case WSAEINPROGRESS://：一个阻塞的WINDOWS套接口调用正在运行中。
                {

                } break;
            case WSAENOTCONN://：套接口未连接（仅适用于SOCK_STREAM类型套接口）。
                {

                } break;
            case WSAENOTSOCK://：描述字不是一个套接口。
                {

                } break;
            default:
                break;
            }
    #endif
        }
        
        return ret >= 0;
    }

    int HNSocket::isConnected()
    {
        fd_set	fd;
        struct timeval tv;

        FD_ZERO(&fd);
        FD_SET(_socket, &fd);

        tv.tv_sec = 0;
        tv.tv_usec = 0;

        if (::select(_socket + 1, nullptr, &fd, nullptr, &tv) > 0)
        {
            if( FD_ISSET(_socket, &fd) )
            {
    #if defined(_WIN32) || defined(WIN32)
                return 1;
    #else
                int nError;
                socklen_t len = sizeof(nError);
                if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0 )
                {
                    return 4;
                }
                if( nError == ECONNREFUSED || nError == ETIMEDOUT )
                {
                    return 4;
                }
                return 1;
    #endif
            }
        }
        return 2;
    }

    bool HNSocket::setNonblocking(bool bNb)
    {
    #if defined(_WIN32) || defined(WIN32)
        unsigned long l = bNb ? 1 : 0;
        int n = ioctlsocket(_socket, FIONBIO, &l);
        if (n != 0)
        {
            printf ("ioctlsocket(FIONBIO) >> %d", Errno);
            return false;
        }
        return true;
    #else
        if (bNb)
        {
            if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1)
            {
                printf ("fcntl(F_SETFL, O_NONBLOCK) %d >>> %s", Errno, strError(Errno));
                return false;
            }
        }
        else
        {
            if (fcntl(_socket, F_SETFL, 0) == -1)
            {
                printf ("fcntl(F_SETFL, 0) %d >>> %s", Errno, strError(Errno));
                return false;
            }
        }
        return true;
    #endif
    }

    bool HNSocket::setSoRcvtimeo(struct timeval& tv)
    {
    #ifdef SO_RCVTIMEO
        if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_RCVTIMEO) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_RCVTIMEO");
        return false;
    #endif
    }

    bool HNSocket::setSoSndtimeo(struct timeval& tv)
    {
    #ifdef SO_SNDTIMEO
        if (setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_SNDTIMEO) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_SNDTIMEO");
        return false;
    #endif
    }

    bool HNSocket::setSoRcvbuf(int x)
    {
    #ifdef SO_RCVBUF
        if (setsockopt(_socket, SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_RCVBUF) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_RCVBUF");
        return false;
    #endif
    }

    bool HNSocket::soRcvbuf()
    {
        int value = 0;
    #ifdef SO_RCVBUF
        socklen_t len = sizeof(value);
        if (setsockopt(_socket, SOL_SOCKET, SO_RCVBUF, (char *)&value, sizeof(len)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_RCVBUF) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_RCVBUF");
        return false;
    #endif
    }


    bool HNSocket::setSoSendbuf(int x)
    {
    #ifdef SO_SNDBUF
        if (setsockopt(_socket, SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_SNDBUF) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_SNDBUF");
        return false;
    #endif
    }

    bool HNSocket::soSendbuf()
    {
        int value = 0;
    #ifdef SO_SNDBUF
        socklen_t len = sizeof(value);
        if (setsockopt(_socket, SOL_SOCKET, SO_SNDBUF, (char *)&value, sizeof(len)) == -1)
        {
            printf ("setsockopt(SOL_SOCKET, SO_SNDBUF) >> %d >> %s", Errno, strError(Errno));
            return false;
        }
        return true;
    #else
        printf ("socket option not available >> %d >> %s", 0, "SO_SNDBUF");
        return false;
    #endif
    }

    unsigned short HNSocket::getSockPort()
    {
        struct sockaddr_in sa;
        socklen_t sockaddr_length = sizeof(struct sockaddr_in);
        if (getsockname(_socket, (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
        {
            memset(&sa, 0, sizeof(sa));
        }
        return ntohs(sa.sin_port);
    }

    void HNSocket::setIp(const std::string& ip)
    {
        _ip = ip;
        
        struct addrinfo addr;
        struct addrinfo* pAddr = &addr;
        
        int nRet = getaddrinfo(ip.c_str(), nullptr, nullptr, &pAddr);
        
        if(nRet != 0)
        {
            _ai_family = AF_UNSPEC;
            return;
        }
        
        _ai_family = pAddr->ai_family;
        
    }
}
