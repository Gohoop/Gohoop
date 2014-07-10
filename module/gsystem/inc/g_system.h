/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    g_system.h
* @version     
* @brief      
* @author   duye
* @date     2013-11-15
* @note 
*
*  3. 2014-07-10 duye move to gsystem module
*  2. 2014-06-21 duye move to gohoop project 
*  1. 2013-11-15 duye Created this file
* 
*/

#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/** 
 * base type define
 */
typedef char                GInt8;
typedef short		        GInt16;
typedef int                 GInt32;
typedef long long			GInt64;
typedef unsigned char       GUint8;
typedef unsigned short		GUint16;
typedef unsigned int        GUint32;
typedef unsigned long long  GUint64;
typedef int                 GResult;

/** 
 * assert
 */
#define G_ASSERT(x)			assert(x)

/** 
 * result variable for successed
 */
#define G_YES				0

/** 
 * result variable for failed
 */
#define G_NO				-1

/** 
 * limits number for path max length
 */
#define G_PATH_MAX			512

/** 
 * limits number for file name max length
 */
#define G_FILE_NAME_MAX	    256