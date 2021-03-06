/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     g_pipe.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-12-1
* @note 
*
*  2. 2014-06-21 duye move to gohoop 
*  1. 2013-12-01 duye Created this file
* 
*/
#include <g_pipe.h>

namespace gsys {

bool Pipe::orgOpen(const GInt8* pipeName, const GInt32 mode)
{
    if (pipeName == NULL)
    {
        return false;
    }

    if (access(pipeName, F_OK) == -1)
    {
        if (mkfifo(pipeName, 0777) != 0)
        {
            return false;
        }
    }    

    m_pipefd = ::open(pipeName, mode);
    if (m_pipefd == -1)
    {
        return false;
    }

    return true;   
}

bool WritePipe::open(const GInt8* pipeName)
{
    return orgOpen(pipeName, O_WRONLY | O_NONBLOCK);          
}

GInt64 WritePipe::write(const GInt8* data, const GUint64 length)
{
    if (m_pipefd == -1)
    {
        return -1;
    }

    if (data == NULL)
    {
        return -1;
    }

    if (length == 0)
    {
        return -1;        
    }    

    GInt64 bytes = -1;
    if ((bytes = ::write(m_pipefd, data, length)) == -1)
    {
    	return -1;
    }

    return bytes;    
}

bool ReadPipe::open(const GInt8* pipeName)
{
    return orgOpen(pipeName, O_RDONLY);        
}

GInt64 ReadPipe::read(GInt8* buffer, const GUint64 size)
{
    if (m_pipefd == -1)
    {
    	return -1;
    }

    if (buffer == NULL)
    {
    	return -1;
    }

    if (size == 0)
    {
    	return -1;       
    }

    GInt32 bytes = -1;
    if ((bytes = ::read(m_pipefd, buffer, size)) == -1)
    {
    	return -1;
    }

    return bytes;    
}
}
