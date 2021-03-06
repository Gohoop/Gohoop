/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_socket.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-2-16
* @note 
*
*  2. 2014-06-21 duye move to gohoop 
*  1. 2014-02-16 duye Created this file
* 
*/
#include <net/if.h>
#include <unistd.h>
#include <g_sys.h>

#include <g_socket.h>

namespace gsys {
	
static const GInt8* G_LOG_PREFIX = "gohoop.system.socket";

const struct in6_addr IN6ADDR_ANY = IN6ADDR_ANY_INIT;

SockAddr::SockAddr() : SockAddr(INADDR_ANY, 0) {}
SockAddr::SockAddr(const GUint32 ip, const GUint16 port)
{
    m_addrLen = sizeof(sockaddr_in);
    bzero(&m_addr, m_addrLen);
    m_addr.sin_family = AF_INET; 
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = htonl(ip); 
}

SockAddr::~SockAddr() {}

void SockAddr::setIp(const GUint32 ip)
{
    m_addr.sin_addr.s_addr = htonl(ip);	
}

GUint32 SockAddr::ip()
{
    return ntohl(m_addr.sin_addr.s_addr);
}

GUint8* SockAddr::ipStr()
{
    return (GUint8*)inet_ntoa(m_addr.sin_addr);
}

void SockAddr::setPort(const GUint16 port)
{
    m_addr.sin_port = htons(port);
}

GUint16 SockAddr::port()
{
    return ntohs(m_addr.sin_port);
}

sockaddr_in& SockAddr::addr()
{
    return m_addr;
}

GUint16 SockAddr::addrLen() const
{
    return m_addrLen;
}

IPv6Addr::IPv6Addr()
{
    m_addrLen = sizeof(sockaddr_in6);
    bzero(&m_sockAddr, m_addrLen);
    m_sockAddr.sin6_family = AF_INET6; 
    m_sockAddr.sin6_port = 0; 
    m_sockAddr.sin6_addr = IN6ADDR_ANY;
}

IPv6Addr::IPv6Addr(const GUint8 ip[16], const GUint16 port)
{
    bzero(&m_sockAddr, sizeof(m_sockAddr));
    m_sockAddr.sin6_family = AF_INET6; 
    m_sockAddr.sin6_port = htons(port);
    memcpy(m_sockAddr.sin6_addr.s6_addr, ip, 16);
}

IPv6Addr::~IPv6Addr() {}

GUint8* IPv6Addr::ip()
{
    return m_sockAddr.sin6_addr.s6_addr;
}

GUint16 IPv6Addr::port()
{
    return ntohs(m_sockAddr.sin6_port);
}

sockaddr_in6& IPv6Addr::addr()
{
    return m_sockAddr;
}

GUint16 IPv6Addr::addrLen() const
{
    return m_addrLen;
}

Socket::Socket() : m_sockfd(-1), m_isInit(false) {}
Socket::~Socket() { close(); }

GResult Socket::open(const NetProtocol& protocol, const std::string& ifName)
{
    GInt32 domain = AF_INET;
    GInt32 sockType = -1;
    GInt32 sockProtocol = -1;
    switch (protocol)
    {
    	case G_IPPROTO_TCP:
    	{
            sockProtocol = IPPROTO_TCP;
            sockType = SOCK_STREAM;
            break;
    	}
    	case G_IPPROTO_UDP:
    	{
    	    sockProtocol = IPPROTO_UDP;
    	    sockType = SOCK_DGRAM;
    	    break;
    	}
    	case G_IPPROTO_SCTP:
    	{
    	    sockProtocol = IPPROTO_SCTP;
    	    setError("[warn]argument protocol(%d) not support (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    return G_NO; // not support
    	}
    	case G_IPPROTO_TIPC:
    	{
    	    //sock_protocol = IPPROTO_TIPC;
    	    setError("[warn]argument protocol(%d) not support (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    return G_NO; // not support
    	}
    	default:
        {
    	    setError("[error]argument protocol(%d) invalid (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    return G_NO;
        }
    }	
	
    m_sockfd = ::socket(domain, sockType, sockProtocol);
    if (m_sockfd < 0)
    {
    	setError("[error]socket(%d, %d, %d) ret=%d invalid (%s:%s:%d)\n", 
    	    domain, sockType, sockProtocol, m_sockfd, __FUNCTION__, __FILE__, __LINE__);
        return G_NO;
    }

    // set non-blocking
    // fcntl(m_sockfd, F_SETFL, O_NONBLOCK)
    
    // init socket option
    initOption(ifName);
    m_isInit = true;
    return G_YES;
}

GResult Socket::close(const GInt32 how)
{
    // SHUT_RD how = 0 : stop receive data
    // SHUT_WR how = 1 : stop send data
    // SHUT_RDWR how = 2 : both above way
    if (!m_isInit)
    {
    	return G_YES;
    }

    //return (shutdown(m_sockfd, how) == 0 ? G_YES : G_NO);
    return ::close(m_sockfd) == 0 ? G_YES : G_NO;
}

GInt32 Socket::sockfd() const
{
    return m_sockfd;	
}

GInt8* Socket::error()
{
    return m_error;
}

GResult Socket::initOption(const std::string& ifName)
{
    GResult ret = G_YES;
    
    // setting specified interface
    struct ifreq interface;
    strncpy(interface.ifr_ifrn.ifrn_name, ifName.c_str(), ifName.length());
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_BINDTODEVICE, (char*)&interface, sizeof(interface)) == -1) 
    {
    	setError("[warn]setsockopt() failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = G_NO;        
    }    
    
    // set address reuse, address reuse flag, 1 reuse
    GInt32 reuse = 1;    
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(GInt32)) == -1)
    {
    	setError("[warn]setsockopt() failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = G_NO;
    }

    // send time limit, unit ms
    int sendTime = 2000;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&sendTime, sizeof(int)) == -1)
    {
    	 ret = false;
    }

    // receive time limit, unit ms
    int recvTime = 2000;    
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&recvTime, sizeof(int)) == -1)
    {
    	 ret = false;
    }

    // set send data buffer size 
    GInt32 sendBufSize = 0xFFFF;    
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&sendBufSize, sizeof(GInt32)) == -1)
    {
    	setError("[warn]setsockopt() failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }

    // set receive data buffer size
    GInt32 recvBufSize = 0xFFFF;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&recvBufSize, sizeof(GInt32)) == -1)
    {
    	setError("[warn]setsockopt() failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }

    // don't copy data from system buffer to socket buffer when send data
    /*
    GInt32 is_copy = 0;    
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&is_copy, sizeof(GInt32)) == -1)
    {
    	setError("[warn]%s:setsockopt() failed (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }

    // don't copy data from system buffer to GSocket buffer when receive data
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&is_copy, sizeof(GInt32)) == -1)
    {
    	setError("[warn]%s:setsockopt() failed (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }
    */

    // let data send completly after execute close GSocket
    /*
    struct STR_Linger
    {
    	GInt16 l_onoff;
    	GInt16 l_linger;
    };

    STR_Linger linger;
    linger.l_onoff = 1;		// 1. allow wait; 0. force close
    linger.l_linger = 1;	// the time of waiting unit s
    if (setsockopt(m_sockfd, SOL_GSocket, SO_LINGER, (const char*)&linger, sizeof(STR_Linger)) == -1)
    {
        ret = false;
    }
    */

    return ret;
}

void Socket::setError(const GInt8* args, ...)
{
    System::pformat(m_error, G_ERROR_BUF_SIZE, args);
}

GInt64 Transfer::send(Socket& socket, const GUint8* data, const GUint64 len, const GInt32 flags)
{
    return ::send(socket.sockfd(), data, len, flags);
}

GInt64 Transfer::sendmsg(Socket& socket, const struct msghdr* msg, const GInt32 flags)
{
    return ::sendmsg(socket.sockfd(), msg, flags);	
}

GInt64 Transfer::sendto(Socket& socket, SockAddr& dst_addr, const GUint8* data, const GUint64 len, const GInt32 flags)
{
    return ::sendto(socket.sockfd(), data, len, flags, (const struct sockaddr*)&dst_addr.addr(), dst_addr.addrLen());	
}

GInt64 Transfer::recv(Socket& socket, GUint8* buffer, const GUint64 size, const GInt32 flags)
{
    return ::recv(socket.sockfd(), buffer, size, flags);
}

GInt64 Transfer::recvmsg(Socket& socket, struct msghdr* msg, const GInt32 flags)
{
    return ::recvmsg(socket.sockfd(), msg, flags);	
}

GInt64 Transfer::recvfrom(Socket& socket, SockAddr& srcAddr, GUint8* buffer, const GUint64 size, const GInt32 flags)
{
    GUint32 addrLen = srcAddr.addrLen();
    return ::recvfrom(socket.sockfd(), buffer, size, flags, (struct sockaddr*)&srcAddr.addr(), &addrLen);	
}

Epoll::Epoll() : m_epollfd(-1), m_maxEvents(0), m_errorHeaderOffset(0)
{
    initError();
}

Epoll::~Epoll() 
{
    close();
}

GResult Epoll::open(const GUint32 maxEvent)
{
    m_maxEvents = maxEvent;
    
    m_epollfd = epoll_create(m_maxEvents);
    if (m_epollfd == -1)
    {
    	setError("[warn]epoll_create failed\n", __FUNCTION__, __FILE__, __LINE__);
    	return G_NO;
    }   
    
    return G_YES;
}

GResult Epoll::close()
{
    if (m_epollfd != -1)
    {
    	::close(m_epollfd);
    	m_epollfd = -1;
    }
    
    return G_YES;
}

GResult Epoll::addfd(const GInt32 fd, const GUint32 events)
{
    IS_YES_RR(m_epollfd == -1, G_NO);
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = events;
    epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &epollEvent);
    return G_YES;
}

GResult Epoll::modfd(const GInt32 fd, const GUint32 events)
{
    IS_YES_RR(m_epollfd == -1, G_NO);
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = events;
    epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &epollEvent);
    return G_YES;
}
	 
GResult Epoll::delfd(const GInt32 fd)
{
    IS_YES_RR(m_epollfd == -1, G_NO);
    epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, nullptr);
    return G_YES;
}

GResult Epoll::wait(EventList& eventList, const GUint32 timeout)
{
    IS_YES_RR(m_epollfd == -1, G_NO);
    struct epoll_event* epollEvents = (struct epoll_event*)calloc(m_maxEvents, sizeof(struct epoll_event));
    GInt32 ret = epoll_wait(m_epollfd, epollEvents, m_maxEvents, timeout);
    if (ret <= 0)
    {
    	free(epollEvents);
    	return G_NO;
    }

    GUint32 evnet_num = ret;
    for (GUint32 i = 0; i < evnet_num; i++)   
    {
        if ((epollEvents[i].events & EPOLLERR) ||  
            (epollEvents[i].events & EPOLLHUP))
        {
            setError("[error]epoll error, close fd\n", __FUNCTION__, __FILE__, __LINE__);
    	    ::close(epollEvents[i].data.fd);
    	    continue;
        }
        else if (epollEvents[i].events & EPOLLIN)
        {
            eventList.push_back(Event(epollEvents[i].data.fd, G_RECV_FD));
        }
		else if (epollEvents[i].events & EPOLLOUT)
		{
		    eventList.push_back(Event(epollEvents[i].data.fd, G_SEND_FD));
		}
		else
		{
		    eventList.push_back(Event(epollEvents[i].data.fd, G_RECV_UN));
		}
    }
    
    free(epollEvents);
    
    return G_YES;
}

GInt8* Epoll::error()
{
    return m_error;
}

void Epoll::initError()
{
    m_errorHeaderOffset = snprintf(m_error, G_ERROR_BUF_SIZE, "[%s]", G_LOG_PREFIX);
}

void Epoll::setError(const GInt8* args, ...)
{
    System::pformat(m_error + m_errorHeaderOffset, G_ERROR_BUF_SIZE - m_errorHeaderOffset, args);
}

ServerSocket::ServerSocket() : m_errorHeaderOffset(0) 
{
    initError();	
}

ServerSocket::~ServerSocket() 
{
    close();
}

GResult ServerSocket::open(const SocketInfo& socket_info)
{
    if (IS_NO(m_socket.open(socket_info.protocol(), socket_info.localIfName())))
    {
    	setError("[error]open socket failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	return G_NO;
    }

    m_socketInfo = socket_info;
    m_addr.setIp(m_socketInfo.serverIp());
    m_addr.setPort(m_socketInfo.serverPort());	
	
    GResult ret = ::bind(m_socket.sockfd(), (const struct sockaddr*)&m_addr.addr(), m_addr.addrLen()) < 0 ? G_NO : G_YES;
    if (IS_NO(ret))
    {
    	setError("[error]bind socket failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	return G_NO;    	
    }
    
    if (socket_info.protocol() == G_IPPROTO_TCP)
    {
        ret = ::listen(m_socket.sockfd(), m_socketInfo.maxConnectNum()) == 0 ? G_YES : G_NO;
        if (IS_NO(ret))
        {
    	    setError("[error]listen socket failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	    return G_NO;        	
        }
    }
    
    return ret;
}

GResult ServerSocket::close()
{
    return m_socket.close();    	
}

GResult ServerSocket::accept(SockAddr& client_addr,  GInt32& sockfd, const RecvMode& mode)
{
    socklen_t addr_len = client_addr.addrLen();
    sockfd = -1;
    
    if (mode == G_RECV_BLOCK)
    {
        sockfd = ::accept(m_socket.sockfd(), (struct sockaddr*)&client_addr.addr(), &addr_len);	
    }
    else if (mode == G_RECV_NONBLOCK)
    {
    	sockfd = ::accept4(m_socket.sockfd(), (struct sockaddr*)&client_addr.addr(), &addr_len, SOCK_NONBLOCK);	
    }
    
    return sockfd > 0 ? G_YES : G_NO;
}

GInt64 ServerSocket::send(const GUint8* data, const GUint64 len)
{
    return Transfer::send(m_socket, data, len, MSG_NOSIGNAL);	
}

GInt64 ServerSocket::sendto(SockAddr& dst_addr, const GUint8* data, const GUint64 len)
{
    return Transfer::sendto(m_socket, dst_addr, data, len, MSG_NOSIGNAL);	
}

GInt64 ServerSocket::recv(GUint8* buffer, const GUint64 size, const RecvMode& mode)
{
    if (mode == G_RECV_BLOCK)
    {
    	return Transfer::recv(m_socket, buffer, size);
    }
    else if (mode == G_RECV_NONBLOCK)
    {
    	return Transfer::recv(m_socket, buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

GInt64 ServerSocket::recvfrom(SockAddr& src_addr, GUint8* buffer, const GUint64 size, const RecvMode& mode)
{
    if (mode == G_RECV_BLOCK)
    {
    	return Transfer::recvfrom(m_socket, src_addr, buffer, size);
    }
    else if (mode == G_RECV_NONBLOCK)
    {
    	return Transfer::recvfrom(m_socket, src_addr, buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

Socket& ServerSocket::socket()
{
    return m_socket;
}
    
GInt8* ServerSocket::error()
{
    return m_error;
}

void ServerSocket::initError()
{
    m_errorHeaderOffset = snprintf(m_error, G_ERROR_BUF_SIZE, "[%s]", G_LOG_PREFIX);
}

void ServerSocket::setError(const GInt8* args, ...)
{
    System::pformat(m_error + m_errorHeaderOffset, G_ERROR_BUF_SIZE - m_errorHeaderOffset, args);
}

ClientSocket::ClientSocket() : m_errorHeaderOffset(0) 
{
    initError();	
}

ClientSocket::~ClientSocket() 
{
    close();
}

GResult ClientSocket::open(const SocketInfo& socket_info)
{
    if (IS_NO(m_socket.open(socket_info.protocol(), socket_info.localIfName())))
    {
    	setError("[error]Socket not init (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	return G_NO;
    }

    m_socketInfo = socket_info;
    m_addr.setIp(m_socketInfo.serverIp());
    m_addr.setPort(m_socketInfo.serverPort()); 	
    
    return ::connect(m_socket.sockfd(), (const struct sockaddr*)&m_addr.addr(), m_addr.addrLen()) < 0 ? G_NO : G_YES;
}

GResult ClientSocket::close()
{
    return m_socket.close();
}

GInt64 ClientSocket::send(const GUint8* data, const GUint64 len)
{
    return Transfer::send(m_socket, data, len, MSG_NOSIGNAL);	
}

GInt64 ClientSocket::sendto(SockAddr& dst_addr, const GUint8* data, const GUint64 len)
{
    return Transfer::sendto(m_socket, dst_addr, data, len, MSG_NOSIGNAL);	
}

GInt64 ClientSocket::recv(GUint8* buffer, const GUint64 size, const RecvMode& mode)
{
    if (mode == G_RECV_BLOCK)
    {
    	return Transfer::recv(m_socket, buffer, size);
    }
    else if (mode == G_RECV_NONBLOCK)
    {
    	return Transfer::recv(m_socket, buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

GInt8* ClientSocket::error()
{
    return m_error;
}

void ClientSocket::initError()
{
    m_errorHeaderOffset = snprintf(m_error, G_ERROR_BUF_SIZE, "[%s]", G_LOG_PREFIX);
}

void ClientSocket::setError(const GInt8* args, ...)
{
    System::pformat(m_error + m_errorHeaderOffset, G_ERROR_BUF_SIZE - m_errorHeaderOffset, args);
}
}
