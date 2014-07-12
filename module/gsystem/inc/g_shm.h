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
 * GShm error code
 */
typedef enum 
{ 
    /** 
     * open GShm failed
     */        
    OPEN_GShm_FAILED = -2,
    /** 
     * munmap failed
     */           
    MUNMAP_GShm_FAILED = -3,
    /** 
     * mmap failed
     */           
    MMAP_GShm_FAILED = -4,
    /** 
     * sync GShm failed
     */           
    SYNC_GShm_FAILED = -5,
    /** 
     * write GShm parameter failed
     */           
    WRITE_GShm_PARA_FAILED = -6,
    /** 
     * read GShm parameter failed
     */           
    READ_GShm_PARA_FAILED = -7,
    /** 
     * GShm not init
     */           
    GShm_NO_INIT = -8,
    /** 
     * GShm path is empty
     */           
    GShm_PATH_EMPTY = -9
} GShmErrorCode;

/** 
 * shared memory for ipc
 */
class GShm
{
public:
    GShm();   
    /**
     * constructor
	 * @param [in] GShmPath : shm mapping file path
	 * @param [in] GShmSize : shm size
	 * @return true/false
     * @note 
     */		
    GShm(const GInt8* shmPath, const GUint64 shmSize);
    ~GShm();

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
	 * @param [in] offset : offset of GShm
	 * @param [in] data : input data
	 * @param [in] size : write size     
     * @return G_YES/G_NO  
     * @note 
     */		
    GResult writeShm(const GUint32 offset, const GInt8* data, const GUint32 length);

    /**
     * read data from shm
	 * @param [in] offset : offset of GShm
	 * @param [in] buffer : output buffer
	 * @param [in] size : read size    
     * @return G_YES/G_NO  
     * @note 
     */	
    GResult readShm(const GUint32 offset, GInt8* buffer, const GUint32 size);

private:
    /**
     * init the GShm
     * @return G_YES/G_NO  
     * @note 
     */	    	
    GResult init();
   
    /**
     * uninit the GShm
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