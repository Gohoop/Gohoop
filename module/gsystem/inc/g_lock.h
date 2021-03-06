/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    g_lock.h
* @version     
* @brief      
* @author   duye
* @date	    2013-11-26
* @note 
*
* 4. 2014-06-20 duye move to gohoop project
* 3. 2014-01-09 duye Add comments
* 2. 2014-01-04 duye 
*     a. Modify GMutex function GTryLock to GTryLock()
*     b. Add function GTryLock() for class GOrgLock
*     c. Modify GTryLock class implimenting
*
* 1. 2013-11-26 duye Created this file
*/

#pragma once

#include <pthread.h>
#include <unistd.h>
#include <g_type.h>

namespace gsys {
	
/** 
 * @brief POSIX GMutex wrapper
 */
class Mutex
{
public:
    /**
     * @brief constructor
     * @note default GMutex type is PTHREAD_GMutex_RECURSIVE
     */	
     Mutex();
	
    /**
     * @brief constructor
     * @param [in] kind : GMutex type
     * @note have four GMutex type, are PTHREAD_GMutex_NORMAL PTHREAD_GMutex_RECURSIVE
     * PTHREAD_GMutex_ERRORCHECK PTHREAD_GMutex_DEFAULT
     */		
    explicit Mutex(const GInt32 kind);

    virtual ~Mutex();
    /**
     * @brief lock GMutex, enter to awaited state
     * @return true/false
     * @note 
     */		
    bool lock();
	
    /**
     * @brief try to lock GMutex, failure return immediately  
     * @return true/false
     * @note 
     */		
    bool tryLock();
	
    /**
     * @brief release lock
     * @return true/false
     * @note 
     */		
    bool unlock();

private:
    /**
     * @brief to prevent copying
     * @note 
     */			
    Mutex(const Mutex&); 
	
    void operator=(const Mutex&);	
	
    /**
     * @brief initialize GMutex
     * @param [in] kind : GMutex type, reference constructor function
     * @note 
     */		
    void init(const GInt32 kind);
    
private:
    pthread_mutex_t	m_mutex;	
};

/** 
 * try lock wrapper
 */
class TryLock
{
public:
    /**
     * @brief constructor
     * @param [in] GMutex : GMutex
     * @param [in] autoUnlock : whether release lock automatic
     * @note 
     */		
    TryLock(Mutex& Mutex, const bool autoUnlock = true);
	
    ~TryLock();

    /**
     * @brief try lock
     * @param [in] timeout : try lock timeout, default is zero, indicate try once, 
     * then return immediately
     * @return true/false
     * @note 
     */		
    bool lock(const GUint32 timeout = 0);

    /**
     * @brief release lock
     * @return true/false
     * @note if construct a release lock, invoke invalid
     */			
    bool unlock();

private:
    /**
     * @brief prevent copying
     * @note
     */	
    TryLock(const TryLock&); 

    /**
     * @brief prevent copying
     * @note
     */		
    void operator=(const TryLock&);	
    
private:
    Mutex&	m_mutex;
    bool	m_autoUnlock;
};

/** 
 * @brief auto lock wrapper
 */
class AutoLock
{
public:
    /**
     * @brief constructor
     * @param [in]GMutex : GMutex
     * @note 
     */			
    explicit AutoLock(Mutex& mutex);
    ~AutoLock();

private:
    /**
     * @brief prevent copying
     * @note
     */		
    AutoLock(const AutoLock&);

    /**
     * @brief prevent copying
     * @note
     */			
    void operator=(const AutoLock&);

private:
    Mutex&      m_mutex;
};
}
