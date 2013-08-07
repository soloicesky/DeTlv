
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
/*           һ���ǽӿڶ���              */

/*
 *@name:isConstructedTag
 *@description:�ж�һ��TAG�Ƿ�����ϵ�tag����ԭʼtag
 *@retval: true ��һ�����tag
 *@retvel: false ��һ��ԭʼtag
*/

boolean isConstructedTag(byte *tag)
{
	return ((tag[0] & 0x20) == 0x20)?true:false;
}

/*
 *@name:parseTag
 *@description:��һ��constructed ��tlv ���н���tag��������tag��ֵ�Լ�tag�ĳ���
 *@param1: tag. ����������tag
 *@param2: tagLen,����������tag�ĳ���
 *@param3: constructedTlvData,����tlvԪ����ɵĴ� 
 *@param4: constructedTlvDataLen,����tlvԪ����ɵĴ��ĳ��� 
 *@retval: ERR_INVALID_PARAMETER �����˲��Ϸ��Ĳ���
 *@retvel: 0 tag�����ɹ�
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

		if((*tag & 0x1F) == 0x1F /*  VALUE_EQUALL(*tag, 0x1F)*/) //�����һ���ֽ�ǰ5bitȫ��1��������к�����tag
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
 *@description:У��һ��tag�Ƿ��ǺϷ���tag
 *@param1: b. ��Ҫ��У���tag
 *@retvel: 0 tag�����ɹ�
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


