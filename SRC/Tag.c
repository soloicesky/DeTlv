
/**********************************************************************
*@filename: Tag.c
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/
#include <stdlib.h>

#include "Tag.h"
#include "ErrorNo.h"

//element define

//end element define

#define VALUE_EQUALL(a,b)	(((a)&(b)) == (b))

//////////////////////////////////////////////////////////////////////
/*           一下是接口定义              */

/*
 *@name:isConstructedTag
 *@description:判断一个TAG是否是组合的tag还是原始tag
 *@retval: true 是一个组合tag
 *@retvel: false 是一个原始tag
*/

boolean isConstructedTag(byte *tag)
{
	return ((tag[0] & 0x20) == 0x20)?true:false;
}

/*
 *@name:parseTag
 *@description:从一串constructed 的tlv 串中解析tag，并返回tag的值以及tag的长度
 *@param1: tag. 解析出来的tag
 *@param2: tagLen,解析出来的tag的长度
 *@param3: constructedTlvData,连续tlv元素则成的串 
 *@param4: constructedTlvDataLen,连续tlv元素则成的串的长度 
 *@retval: ERR_INVALID_PARAMETER 传入了不合法的参数
 *@retvel: 0 tag解析成功
*/

int32 parseTag(byte *tag, byte *tagLen, byte **constructedTlvData, int32 *constructedTlvDataLen)
{	
	if(constructedTlvData == NULL || constructedTlvDataLen == NULL || \
	   tag == NULL || tagLen == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	while(*constructedTlvDataLen > 0)
	{
		*tag = **constructedTlvData;
		*constructedTlvData += 1;
		*tagLen = 1;
		*constructedTlvDataLen -= 1;

		if(*tag == 0xFF || *tag == 0x00)
		{
			continue;
		}

		if(*constructedTlvDataLen < 0)
		{
			return ERR_PARSE_TAG;
		}

		if((*tag & 0x1F) == 0x1F /*  VALUE_EQUALL(*tag, 0x1F)*/) //如果第一个字节前5bit全是1则表明还有后续的tag
		{
			do{
				tag[*tagLen] = **constructedTlvData;
				*tagLen += 1;
				*constructedTlvDataLen -= 1;			
				*constructedTlvData += 1;

				if(*constructedTlvDataLen < 0)
				{
					return ERR_PARSE_TAG;
				}
			}while((tag[*tagLen - 1] & 0x80) == 0x80/* VALUE_EQUALL(tag[*tagLen - 1], 0x80)*/);

			break;
		}
	}

	return 0;
}

/*
 *@name:validate
 *@description:校验一个tag是否是合法的tag
 *@param1: b. 需要被校验的tag
 *@retvel: 0 tag解析成功
*/

void validate(byte* b) {

	//add your to do here
	#if 0
        if (b == NULL || b.length == 0) {
            throw new IllegalArgumentException("Tag must be constructed with a non-empty byte array");
        }
        if (b.length == 1) {
            if ((b[0] & (byte) 0x1F) == (byte) 0x1F) {
                throw new IllegalArgumentException("If bit 6 to bit 1 are set tag must not be only one byte long");
            }
        } else {
            if ((b[b.length - 1] & (byte) 0x80) != (byte) 0x00) {
                throw new IllegalArgumentException("For multibyte tag bit 8 of the final byte must be 0: " + Integer.toHexString(b[b.length - 1]));
            }
            if (b.length > 2) {
                for (int i = 1; i < b.length - 1; i++) {
                    if ((b[i] & (byte) 0x80) != (byte) 0x80) {
                        throw new IllegalArgumentException("For multibyte tag bit 8 of the internal bytes must be 1: " + Integer.toHexString(b[i]));
                    }
                }
            }
        }
	#endif
}


