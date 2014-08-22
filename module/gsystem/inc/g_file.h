/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		g_file.h
* @version     
* @brief      
* @author	duye
* @date		2014-06-20
* @note 
*
*  1. 2014-06-20 duye Created this GFile
* 
*/

#pragma once

#include <sys/stat.h>
#include <g_type.h>
#include <g_sys.h>

/** 
 * file open flags
 */
typedef enum
{
	G_OPEN_READ = 1,
	G_OPEN_WRITE = 2,
	G_OPEN_RDWR = 4,
	G_OPEN_APPEND = 8
} GFileOpenFlags;

/** 
 * seek flags
 */
typedef enum
{
	G_SEEK_BEG = 1,
	G_SEEK_CUR,
	G_SEEK_END
} GFileSeekFlags;

/** 
 * file utility
 */
class GFileUtil
{
public:
	/**
	 * @brief create file
	 * @param [in] filePath : file path
	 * @return G_YES/G_NO
	 * @note 
	 */	
	static GResult createFile(const GInt8* filePath); 

	/**
	 * @brief create file
	 * @param [in] filePath : file path
	 * @param [in] initSize : file initialization size
	 * @return G_YES/G_NO
	 * @note 
	 */	
	static GResult createFile(const GInt8* filePath, const GUint64& initSize);     
};

/** 
 * file operation wrapper
 */
class GFile
{
public:
	GFile();

	/**
	 * @brief set file path
	 * @param [in] GFilePath : GFile path
	 * @note 
	 */	    
	explicit GFile(const GInt8* filePath);

	~GFile();

	/**
	 * @brief open file for reading
	 * @param [in] fileOpenFlags : open mode flags, from type OpenFlags
	 * @return G_YES/G_NO
	 * @note 
	 */		
	GResult open(const GFileOpenFlags fileOpenFlags);

	/**
	 * @brief open file for reading
	 * @param [in] fileOpenFlags : open mode flags, from type OpenFlags
	 * @param [in] fileOpenMode : permission
	 * @return G_YES/G_NO
	 * @note 
	 */		
	GResult open(const GFileOpenFlags fileOpenFlags, const GInt32 fileOpenMode);	

	/**
	 * @brief close file
	 * @return G_YES/G_NO
	 * @note 
	 */		
	GResult close();

	/**
	 * @brief get file size
	 * @param [out] buffer : output buffer
	 * @param [in] size : the size of buffer     
	 * @return size/G_NO
	 * @note 
	 */			
	GInt64 getSize();

	/**
	 * @brief set file seek
	 * @param [in] offset : offset
	 * @param [in] flags : G_SEEK_BEG,G_SEEK_CUR,G_SEEK_END  
	 * @return offset/G_NO
	 * @note 
	 */			
	GInt64 seek(const GInt64 offset, const SeekFlags& flags);	

	/**
	 * @brief get file pointer offset from header
	 * @return offset from file header
	 * @note 
	 */			
	GInt64 tell();

	/**
	 * @brief read file
	 * @param [out] buffer : output buffer
	 * @param [in] size : the size of buffer     
	 * @return size/-1
	 * @note 
	 */			
	GInt64 read(GInt8* buffer, const GUint64 size);

	/**
	 * @brief write file
	 * @param [in] buffer : input buffer
	 * @param [in] size : the size of buffer
	 * @return size/-1
	 * @note 
	 */		
	GInt64 write(const GInt8* data, const GUint64 length);

	/**
	 * @brief get last error string
	 * @param [out] error : output buffer
	 * @param [in] size : output buffer size
	 * @return G_YES/G_NO
	 * @note 
	 */		
	GInt8* getError();	

	private:
	/**
	 * @brief origin API for open file
	 * @param [in] flags : operation flags
	 * @param [in] mode : operation mode
	 * @return G_YES/G_NO
	 * @note 
	 */			
	GResult orgOpen(const GInt32 flags, const GUint32 mode);

	/**
	 * @brief origin set program running error
	 * @param [in] error : error string
	 * @note 
	 */		
	void setError(const GInt8* args, ...);

private:
	GInt32		m_fd;
	GInt32		m_flags;
	GInt8		m_path[G_PATH_MAX];
	GUint32		m_pathLen;
	GInt8		m_error[G_ERROR_BUF_SIZE];
};
