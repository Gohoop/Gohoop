/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_ftp_client.h
* @version     
* @brief      
* @author   duye
* @date     2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
* 
*/
#pragma once

#include <g_network_client.h>

namespace gcom {

class FtpClient : public NetworkClient
{
public:
    FtpClient();
    
    /**
     * @brief constructor
     * @param [in] server_addr : ftp server address
     * @param [in] net_card : network card for communication, defualt is eth0
     */
    explicit FtpClient(const IPPortPair& server_addr, const std::string& net_card = "eth0");
    virtual ~FtpClient();
	
    /**
     * @brief to connect ftp server
     * @return G_YES/G_NO
     * @note derive class implemention
     */
    GResult connect();
    
    /**
     * @brief to connect ftp server
     * @param [in] server_addr : server address
     * @param [in] server_addr : ftp server address
     * @param [in] net_card : network card for communication, defualt is eth0     
     * @return G_YES/G_NO
     * @note derive class implemention
     */
    GResult connect(const IPPortPair& server_addr, const std::string& net_card = "eth0");
	
    /**
     * @brief send message
     * @param [in] data : by sent data
     * @param [in] len : data length
     * @return have sent size, -1 failed
     * @note derive class implemention
     */
    GInt64 sendMsg(const GInt8* data, const GUint64 len);
	
    /**
     * @brief message loop handle, new thread
     * @note derive class implemention
     * @return G_YES/G_NO
     */
    GResult routine();	
	
private:
    NetworkClient*	m_tcpClient;
    NetworkClient*	m_udpClient;
};
}
