/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_tcp_server.h
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

#include <g_socket.h>
#include <g_network_server.h>

namespace gcom {
	
/**
 * @brief connect state
 */
typedef enum
{
    // don't connect state
    TCP_CON_STATE_OFF,
    // connected state
    TCP_CON_STATE_CON,
    // idle state
    TCP_CON_STATE_IDLE,
    // closed state
    TCP_CON_STATE_CLOSED
} TcpConnectState;

/**
 * @brief tcp server user interface
 */
class TcpServerInterface
{
public:
    virtual ~TcpServerInterface() {}
    virtual GResult accepted(const SocketAddr& clientAddr) = 0;
};

class ClientAgent;

/**
 * @brief tcp server
 */
class TcpServer : public NetworkServer
{
public:
    typedef std::list<ClientAgent*> ClientAgentList;
    
public:
    TcpServer();

    /**
     * @brief constructor
     * @param [in] server_addr : ftp server address
     * @param [in] net_card : network card for communication, defualt is eth0
     */    
    explicit TcpServer(const IPPortPair& serverAddr, const std::string& net_card = "eth0");
    virtual ~TcpServer();
	
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
     * @brief restart service
     * @return G_YES/NO
     */
    GResult restart();

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
    GResult routine();      
    
private:
    gsys::ServerSocket  m_serverSocket;
    gsys::Epoll         m_epoll;
    ClientAgentList     m_clientAgentList;
};

/**
 * @brief client agent
 */
class ClientAgent
{
public:
    ClientAgent();
    ClientAgent(const GInt32 sockfd, const SockAddr& client_addr);
    ~ClientAgent();
  
    /**
     * @brief set/get sock fd
     * @return sock fd
     */
    void setSockfd(const GInt32 sockfd);
    GInt32 sockfd() const;
    
    /**
     * @brief set/get client address
     * @return client address
     */
    void setClientAddr(const SockAddr& client_addr);
    SockAddr& clientAddr();

private:
    GInt32    m_sockfd;
    SockAddr  m_clientAddr;
};
}
