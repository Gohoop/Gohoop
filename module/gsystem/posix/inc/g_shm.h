/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     g_shm.h
* @version     
* @brief      
* @author   duye
* @date     2014-02-22
* @note 
*
*  2. 2014-06-20 duye move to gohoop project 
*  1. 2014-02-22 duye Created this file
* 
*/

#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <g_type.h>

/** 
 * shm error code
 */
typedef enum 
{ 
    /** 
     * open shm failed
     */        
    OPEN_SHM_FAILED = -2,
    /** 
     * munmap failed
     */           
    MUNMAP_SHM_FAILED = -3,
    /** 
     * mmap failed
     */           
    MMAP_SHM_FAILED = -4,
    /** 
     * sync shm failed
     */           
    SYNC_SHM_FAILED = -5,
    /** 
     * write shm parameter failed
     */           
    WRITE_SHM_PARA_FAILED = -6,
    /** 
     * read shm parameter failed
     */           
    READ_SHM_PARA_FAILED = -7,
    /** 
     * shm not init
     */           
    SHM_NO_INIT = -8,
    /** 
     * shm path is empty
     */           
    SHM_PATH_EMPTY = -9
} ShmErrorCode;

/** 
 * shared memory for ipc
 */
class Shm
{
public:
    Shm();   
    /**
     * constructor
	 * @param [in] shmPath : shm mapping file path
	 * @param [in] shmSize : shm size
	 * @return true/false
     * @note 
     */		
    Shm(const GInt8* shmPath, const GUint64 shmSize);
    ~Shm();

    /**
     * set shm mapping file path
	 * @param [in] shmPath : shm mapping file path     
     * @note 
     */	
    void setShmPath(const GInt8* shmPath);

    /**
     * set shm mapping file path
	 * @return shm mapping file path   
     * @note 
     */	
    GInt8* getShmPath();

    /**
     * set shm mapping file size
     * @param [in] shmSize : shm size  
     * @note 
     */		
    void setShmSize(const GUint64 shmSize);

    /**
     * get shm mapping file size
     * @return shm mapping file size   
     * @note 
     */	    
    GUint64 getShmSize() const;    
   
    /**
     * sync the shm
     * @return G_YES/G_NO  
     * @note 
     */	
    GResult syncShm();
   
    /**
     * write data to shm
	 * @param [in] offset : offset of shm
	 * @param [in] data : input data
	 * @param [in] size : write size     
     * @return G_YES/G_NO  
     * @note 
     */		
    GResult writeShm(const GUint32 offset, const GInt8* data, const GUint32 length);

    /**
     * read data from shm
	 * @param [in] offset : offset of shm
	 * @param [in] buffer : output buffer
	 * @param [in] size : read size    
     * @return G_YES/G_NO  
     * @note 
     */	
    GResult readShm(const GUint32 offset, GInt8* buffer, const GUint32 size);

private:
    /**
     * init the shm
     * @return G_YES/G_NO  
     * @note 
     */	    	
    GResult init();
   
    /**
     * uninit the shm
     * @return G_YES/G_NO  
     * @note 
     */	 	
	GResult uninit();

private:
	GInt8		    m_shmPath[G_PATH_MAX];
	GUint64			m_shmSize;	
	void*			m_shmAddr;
	bool            m_initFlags;
};