/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     g_rpc_server.h
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

#include <g_network_server.h>

namespace gcom {

class RpcServer : public NetworkServer
{
public:
    RpcServer();
    
    /**
     * @brief constructor
     * @param [in] server_addr : ftp server address
     * @param [in] net_card : network card for communication, defualt is eth0
     */    
    explicit RpcServer(const IPPortPair& server_addr, const std::string& net_card = "eth0");
    ~RpcServer();

    /**
     * @brief startup service
     * @return G_YES/G_NO
     */       
    GResult start();

    /**
     * @brief startup service
     * @param [in] server_addr : ftp server address
     * @param [in] net_card : network card for communication, defualt is eth0
     * @return G_YES/G_NO
     */      
    GResult start(const IPPortPair& server_addr, const std::string& net_card = "eth0");

    /**
     * @brief stop service
     * @return G_YES/G_NO
     */
    GResult stop();   

    /**
     * @brief message loop handle, new thread
     * @note derive class implemention
     * @return G_YES/G_NO
     */
    GResult msgLoop();      
};
}
