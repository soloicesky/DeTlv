//系统头文件
#include <stdlib.h>

//自定义头文件
#include "TlvDecoder.h"
#include "Tag.h"
#include "ErrorNo.h"
#include "TlvDecoderErrorNo.h"

int validateConstructedTlvData(byteArray constructedTlvData, uint16 constructedTlvDataLen)
{
	if(constructedTlvData == NULL ||  \
		constructedTlvDataLen < MIN_CONSTRUCTEDTLVDATA_LEN)
	{
		return ERR_INVALID_TLVDATA;
	}

	return 0;
}



static int parseLength(int32 *lengthLen, byteArray * data, int32 *constructedTlvDataLen) {
	int lengthByte = **data;
	int lenByteCounts;

	if(lengthLen == NULL ||  data == NULL ||\
		constructedTlvDataLen == NULL)
	{
		return ERR_INVALID_TLVDATA;
	}
	
	if ((lengthByte & 0x80) == 0x80) 
	{
		lenByteCounts = (lengthByte & 0x7F);
		*constructedTlvDataLen -= lenByteCounts;

		if(*constructedTlvDataLen < 0)
		{
			return ERR_PARSE_LENGTH;
		}
		
		while (lenByteCounts > 0) 
		{
			*lengthLen += **data & 0xFF;
			
			if (lenByteCounts > 1) 
			{
				*lengthLen *= 256;
			}
			
			lenByteCounts--;
			*data += 1;
		}

	}
	else 
	{
		*lengthLen = lengthByte;
	}

	if(*constructedTlvDataLen <= 0)
	{
		return ERR_PARSE_LENGTH;
	}
	
	*data += 1;
	*constructedTlvDataLen -= 1;
	
	return 0;
}



int32 decodeConstructedTlvData(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, boolean parseConstructedTags)
{
	byte tag[TAG_LENGTH];
	byte tagLen;
	int32 length;
	int32 tempLen = 0;
	byteArray value = NULL;
	saveTlvElement saveTlvEle = NULL;  //保存TLV元素接口如果是constructed ber-tl则用此接口保存
	saveTlElement  saveTlEle = NULL; ////保存TL元素接口如果是constructed tags则用此接口保存

	if(constructedData == NULL || constructedDataLen < 2)
	{
		return ERR_INVALID_PARAMETER;
	}

	while(constructedDataLen > 0)
	{
		if (parseTag(tag, &tagLen, &constructedData, &constructedDataLen) != 0)
		{
			return ERR_PARSE_TAG;
		}

		if (parseLength(&length, &constructedData, &constructedDataLen) != 0)
		{ 
			return ERR_PARSE_LENGTH;
		}		

		if(true == parseConstructedTags)
		{
			if(saveDataCallback != NULL)
			{
				saveTlEle = (saveTlElement)saveDataCallback;
				
				if(saveTlEle(tag, tagLen, length) != 0)
				{
					return ERR_SAVEDATA_FAIL;
				}
			}

			continue;
		}
		else
		{
			value = (byteArray) malloc(sizeof(byte) * (length + 1)); //预留一个空间做冗余防止溢出

			if(value == NULL)
			{
				return ERR_MEMALLOC_VALUE;
			}

			constructedDataLen -= length;

			if(constructedDataLen < 0)
			{
				return ERR_PARSE_VALUE;
			}
			
			memcpy(value, constructedData, length);
			constructedData += length;

			
			if(saveDataCallback != NULL)
			{
				saveTlvEle = (saveTlvElement)saveDataCallback;
				
				if(saveTlvEle(tag, tagLen, length, value) != 0)
				{
					free(value);
					value = NULL;
					return ERR_SAVEDATA_FAIL;
				}
			}

			if(isConstructedTag (tag))
			{
				return decodeConstructedTlvData(saveDataCallback, value,length, parseConstructedTags);
			}

			if((length + 1) > tempLen)
			{
				free(value);
				value = NULL;
				tempLen = (length + 1);
			}
		}
	}

	if(constructedDataLen < 0)
	{
		return ERR_PARSE_VALUE;
	}

	free(value);
	value = NULL;
	return 0;
}

boolean checkTlvExist(uint16 tagToCheck, byteArray *constructedData, 
						uint16 *constructedDataLen, boolean parseConstructedTags)
{
	byte tag[TAG_LENGTH];
	byte tagLen;
	int32 length;
	int32 tempLen = 0;
	byteArray value = NULL;
	
	if(constructedData == NULL)
	{
		return false;
	}

	while(constructedDataLen > 0)
	{
		if (parseTag(tag, &tagLen, constructedData, constructedDataLen) != 0)
		{
			return false;
		}

		if(memcmp(tag, &tagToCheck, sizeof(tag)) == 0) //find it
		{
			if(value != NULL)
			{
				free(value);
				value = NULL;
			}

			return true;
		}

		if (parseLength(&length, constructedData, constructedDataLen) != 0)
		{ 
			return false;
		}		

		if(true == parseConstructedTags)
		{
			continue;
		}
		else
		{
			value = (byteArray) malloc(sizeof(byte) * (length + 1)); //预留一个空间做冗余防止溢出

			if(value == NULL)
			{
				return false;
			}

			memcpy(value, *constructedData, length);
			constructedDataLen -= length;
			constructedData += length;

			if(isConstructedTag (tag))
			{
				return checkTlvExist(tagToCheck, &value,&length, parseConstructedTags);
			}

			if((length + 1) > tempLen)
			{
				free(value);
				value = NULL;
				tempLen = (length + 1);
			}
		}
	}

	free(value);
	value = NULL;
	return false;
}


boolean validateTemplate(byteArray templateData, uint16 dataLen)
{
	if(templateData == NULL)
	{
		return false;
	}


	return true;
}


