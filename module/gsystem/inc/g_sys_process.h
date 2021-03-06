/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_sys_process.h
* @version     
* @brief      
* @author   duye
* @date	    2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
* 
*/
#pragma once
#include <g_result.h>
#include <g_type.h>

namespace gsys {
    
/**
 * @brief signal type
 */
typedef enum
{
    G_SIGSEGV = 0,
    G_SIGINT,
} SignalType;

/**
 * @brief system callback observer
 */
class SysProcess
{
public:
    SysProcess();
    ~SysProcess();
    
    /**
     * @brief setting the number of one process can open files
     * @param [in] limit_file : can open file number
     * @return G_YES/G_NO
     */
    GResult setLimitFile(const GUint32 limit_file);  
    GUint32 limitFile() const;
    
private:
    GUint32    m_limitFile;
};

/**
 * @brief system callback observer
 */
class ProcessSysCallbackObserver
{
public:
    virtual ~ProcessSysCallbackObserver() {}

    /**
     * @brief system signal handler
     * @param [in] sig : signal
     */    
    virtual void onSignalHandler(const GInt32 sig) = 0;
};

/**
 * @biref process monitor for system API callback
 */
class ProcessSysCallback
{
public:
    ProcessSysCallback();
    ~ProcessSysCallback();
    
    /**
     * @brief regist process system callback observer
     * @param [in] observer : observer
     */
    void registObserver(ProcessSysCallbackObserver* observer);
    
    /**
     * @brief system signal callback
     * @param [in] sig : signal
     */
    static void signalHandler(const GInt32 sig);

private:
    static ProcessSysCallbackObserver*  m_observer;
};

}
