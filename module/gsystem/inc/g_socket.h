/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		g_socket.h
* @version     
* @brief      
* @author	duye
* @date		2014-02-16
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

/** 
 * @brief posix socket wrapper class
 */
class GSocket
{
public:
	GSocket();

	/**
	 * @brief constructor
	 * @param [in] ip : ip address
	 * @param [in] port : port
	 * @note 
	 */			
	GSocket(const GUint32 ip, const GUint16 port);

	/**
	 * @brief copy constructor
	 * @param [in] socket : socket
	 * @note 
	 */			
	GSocket(const GSocket& socket);
	~GSocket();

	/**
	 * @brief init socket
	 * @param [in] domain : domain
	 * @param [in] type : socket type
	 * @return G_YES/G_NO
	 * @note 
	 */		
	GResult openSocket(const GInt32 domain = AF_INET, const GInt32 type = SOCK_STREAM/*SOCK_DGRAM*/);
			
	/**
	 * @brief send data
	 * @param [in] data : send data
	 * @param [in] dataLen : data length
	 * @param [in] flags : flags
	 * @return size/-1
	 * @note 
	 */		
	GInt64 sendData(const GUint8* data, const GUint64 length, const GInt32 flags = MSG_NOSIGNAL);

	/**
	 * @brief receive data
	 * @param [out] buffer : output buffer
	 * @param [in] bufferSize : buffer size
	 * @param [in] flags : flags
	 * @return size/-1
	 * @note 
	 */	
	GInt64 recvData(GUint8* buffer, const GUint64 size, const GInt32 flags = 0);

	/**
	 * @brief shutdown connecting
	 * @param [in] how : way
	 * @return G_YES/G_NO
	 * @note 
	 */	
	GResult closeSocket(const GInt32 how = 0);
		
	/**
	 * @brief setting address
	 * @param [in] ip : ip address
	 * @param [in] port : port
	 * @note 
	 */		
	void setAddr(const GUint32 ip, const GUint16 port);

	/**
	 * @brief get ip address
	 * @return ip address
	 */		
	GUint32 getIP() const;

	/**
	 * @brief get port
	 * @return port
	 */		
	GUint16 getPort() const;

private:
	/**
	 * @brief setting socket options 
	 * @return G_YES/G_NO
	 */		
	GResult initOption();

private:
	// GSocket file descrition
	GInt32		m_sockfd;
	// address
	sockaddr_in	m_addr;
	// address length
	socklen_t	m_addrLen;			
};