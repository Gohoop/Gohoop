/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		g_datainputstream.h
* @version     
* @brief      
* @author   ylh
* @date     2014-07-08
* @note 
*
*  1. 2014-07-08 ylh Created this file
* 
*/

#pragma once

#include <g_system.h>
#include <g_namespace.h>
#include <g_filterinputstream.h>
#include <g_datainput.h>

namespace gcom {

class DataInputStream : public FilterInputStream, public DataInput
{
public:
	DataInputStream(std::shared_ptr<InputStream> in); 
	virtual ~DataInputStream();

	virtual bool readBool() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GInt8 readChar() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GInt16 readShort() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GInt32 readInt() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GInt64 readLong() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GUint8 readUnsignedChar() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GUint16 readUnsignedShort() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GUint32 readUnsignedInt() throw(std::ios_base::failure, GCommon::EOFException);
	virtual GUint64 readUnsignedLong() throw(std::ios_base::failure, GCommon::EOFException);
	virtual std::string readLine() throw(std::ios_base::failure, GCommon::EOFException);

	virtual void readFully(GInt8* buffer, GInt32 bufferLen) throw(std::ios_base::failure, std::logic_error, GCommon::EOFException);
	virtual void readFully(GInt8* buffer, GInt32 bufferLen, GInt32 offset, GInt32 len) throw(std::ios_base::failure, std::logic_error, GCommon::EOFException);
};
}
