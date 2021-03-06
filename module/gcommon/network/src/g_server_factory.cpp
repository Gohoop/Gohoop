/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_server_factory.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-10-12
* @note 
*
*  1. 2014-10-12 duye Created this file
* 
*/
#include <g_ftp_server.h>
#include <g_http_server.h>
#include <g_rpc_server.h>
#include <g_tcp_server.h>
#include <g_udp_server.h>
#include <g_cli_server.h>
#include <g_server_factory.h>

namespace gcom {

ServerFactory::ServerFactory() {}
ServerFactory::~ServerFactory() {}

NetworkServer* ServerFactory::create(const ServerType& server_type)
{
    NetworkServer* server = nullptr;
    
    switch (server_type)
    {
        case G_SERVER_FTP:
            server = new FtpServer;
            break;
        case G_SERVER_HTTP:
            server = new HttpServer;
            break;
        case G_SERVER_RPC:
            server = new RpcServer;
            break;
        case G_SERVER_TCP:
            server = new TcpServer;
            break;
        case G_SERVER_UDP:
            server = new UdpServer;
            break;
        case G_SERVER_CLI:
            server = new CliServer;
            break;
        default:
            break;
    }
    
    return server;
}

void ServerFactory::destroy(const ServerType& server_type, NetworkServer* server)
{
    switch (server_type)
    {
        case G_SERVER_FTP:
        {    
            FtpServer* del_server = dynamic_cast<FtpServer*>(server);
            delete del_server;
            break;
        }
        case G_SERVER_HTTP:
        {    
            HttpServer* del_server = dynamic_cast<HttpServer*>(server);
            delete del_server;
            break;
        }
        case G_SERVER_RPC:
        {    
            RpcServer* del_server = dynamic_cast<RpcServer*>(server);
            delete del_server;
            break;
        }
        case G_SERVER_TCP:
        {    
            TcpServer* del_server = dynamic_cast<TcpServer*>(server);
            delete del_server;
            break;
        }
        case G_SERVER_UDP:
        {    
            UdpServer* del_server = dynamic_cast<UdpServer*>(server);
            delete del_server;
            break;
        }
        case G_SERVER_CLI:
        {    
            CliServer* del_server = dynamic_cast<CliServer*>(server);
            delete del_server;
            break;
        }
        default:
            break;
    }    
}
}
