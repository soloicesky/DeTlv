/**********************************************************************
*@filename: TlvDecoder.h
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/


#ifndef _TLV_DECODER_H_
#define _TLV_DECODER_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "UserType.h"

#define MIN_CONSTRUCTEDTLVDATA_LEN			2

typedef int32 (*saveTlvElement)(byte *tag, byte tagLen,int32 len, byteArray value);

typedef int32 (*saveTlElement)(byte *tag, byte tagLen,int32 len);


int32 decodeConstructedTlvData(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, boolean parseConstructedTags);

boolean checkTlvExist(uint16 tagToCheck, byteArray *constructedData, 
						uint16 constructedDataLen, uint16 *tagLen,boolean parseConstructedTags);



#ifdef __cplusplus
}
#endif

#endif

