/**********************************************************************
*@filename: TlvDecoder.h
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/


#ifndef _TLV_DECODER_H_
#define _TLV_DECODER_H_


#ifdef _cplusplus
extern "C"
{
#endif

#include "UserType.h"

#define MIN_CONSTRUCTEDTLVDATA_LEN			2

typedef int32 (*saveTlvElement)(byte *tag, byte tagLen,int32 len, byteArray value);

typedef int32 (*saveTlElement)(byte *tag, byte tagLen,int32 len);


int32 decodeConstructedTlvData(void *saveDataInterface,byteArray constructedData,
							int32 constructedDataLen, boolean parseConstructedTags);


#ifdef _cplusplus
}
#endif

#endif

