/**********************************************************************
*@filename: Tag.h
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/


#ifndef _TAG_H_
#define _TAG_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "UserType.h"


#define TAG_LENGTH			3

boolean isConstructedTag(byte *tag);

int32 parseTag(byte *tag, byte *tagLen, byte **constructedTlvData, int *constructedTlvDataLen);


#ifdef __cplusplus
}
#endif

#endif

