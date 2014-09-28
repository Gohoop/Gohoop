/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		g_tcp_client.h
* @version     
* @brief      
* @author   duye
* @date     2014-08-29
* @note 
*
*  1. 2014-08-29 duye Created this file
* 
*/

#pragma once

#include <g_system.h>
#include <g_network.h>

/**
 * @brief tcp client user interface
 */	
class TcpClientInterface
{
public:
	virtual ~TcpClientInterface() {}
	virtual GResult state(const TcpConnectState& state) = 0;
	virtual GResult received(GInt8* data, const GUint64 len) = 0;
};

/**
 * @brief tcp client
 */
class TcpClient
{
public:
	TcpClient();
	explicit TcpClient(const IPPortPair& serverAddr, TcpClientInterface* interface = nullptr);
	~TcpClient();
	
	/**
	 * @brief setting server address
	 */
	void setServerAddr(const IPPortPair& serverAddr);
	
	/**
	 * @brief connect
	 * @return G_YES/G_NO
	 */
	GResult connect();
	
	/**
	 * @brief close
	 * @return G_YES/G_NO
	 */
	GResult close();
	
	/**
	 * @brief send data
	 * @param [in] data : send data
	 * @param [in] len : data length
	 * @return -1:failed, > 0:send size
	 */
	GInt64 send(const GInt8* data, const GUing64 len);
	
	/**
	 * @brief receive data
	 * @param [in] buffer : data buffer
	 * @param [in] size : buffer size
	 * @param [in] timeout : waitting timeout, default is 0, indicate waitting untill has data
	 * @return -1:failed, > 0:received size
	 */
	GInt64 recv(const GInt8* buffer, const GUing64 size, const GUint32 timeout = 0);
	
private:
	IPPortPair			m_serverAddr;
	TcpClientInterface*	m_tcpClientInterface;
};