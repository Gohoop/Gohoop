/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     g_socket.h
* @version     
* @brief      
* @author   duye
* @date     2014-02-16
* @note 
*
*  2. 2014-06-20 duye move to gohoop project 
*  1. 2014-02-16 duye Created this file
* 
*/

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <string>
#include <g_type.h>

G_NS_GCOMMON_BEG 

/** 
 * posix socket wrapper class
 */
class Socket
{
public:
	Socket();
	
    /**
     * constructor
	 * @param [in] ip : ip address
	 * @param [in] port : port
     * @note 
     */			
	Socket(const GUint32 ip, const GUint16 port);

    /**
     * copy constructor
	 * @param [in] socket : socket
     * @note 
     */			
	Socket(const Socket& socket);
	~Socket();
	
    /**
     * init socket
	 * @param [in] domain : domain
	 * @param [in] type : socket type
	 * @return G_YES/G_NO
     * @note 
     */		
	GResult openSocket(const GInt32 domain = AF_INET, const GInt32 type = SOCK_STREAM/*SOCK_DGRAM*/);
			
    /**
     * send data
	 * @param [in] data : send data
	 * @param [in] dataLen : data length
	 * @param [in] flags : flags
	 * @return size/-1
     * @note 
     */		
	GInt64 sendData(const GUint8* data, const GUint64 length, const GInt32 flags = MSG_NOSIGNAL);
	
    /**
     * receive data
	 * @param [out] buffer : output buffer
	 * @param [in] bufferSize : buffer size
	 * @param [in] flags : flags
	 * @return size/-1
     * @note 
     */	
	GInt64 recvData(GUint8* buffer, const GUint64 size, const GInt32 flags = 0);

    /**
     * shutdown connecting
	 * @param [in] how : way
	 * @return G_YES/G_NO
     * @note 
     */	
	GResult closeSocket(const GInt32 how = 0);
		
    /**
     * setting address
	 * @param [in] ip : ip address
	 * @param [in] port : port
     * @note 
     */		
	void setAddr(const GUint32 ip, const GUint16 port);

    /**
     * get ip address
     * @return ip address
     */		
	GUint32 getIP() const;

    /**
     * get port
     * @return port
     */		
	GUint16 getPort() const;

private:
    /**
     * setting socket options 
     * @return G_YES/G_NO
     */		
	GResult initOption();

private:
    // socket file descrition
	GInt32          m_sockfd;
	// address
	sockaddr_in		m_addr;
	// address length
	socklen_t		m_addrLen;			
};

G_NS_END