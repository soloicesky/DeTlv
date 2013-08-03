
#include <stdio.h>

#include "TlvDecoder.h"

//typedef int (*saveTlvElement)(byte *tag, byte tagLen,int32 len, byteArray value);

//typedef int (*saveTlElement)(byte *tag, byte tagLen,int32 len);


int32 saveTLVData(byte *tag, byte tagLen,int32 len, byteArray value)
{
	tchar disp[len * 2 + 1];

	memset(disp, 0x00, sizeof(disp));
	byteArrayToHexString (disp, tag, tagLen);

	printf("TAG:0x%s\r\n", disp);

	printf("LENGTH:%d\r\n", len);

	memset(disp, 0x00, sizeof(disp));
	byteArrayToHexString (disp, value, len);

	printf("VALUE:%s\r\n\r\n", disp);

	return 0;
}

int32 saveTLData(byte *tag, byte tagLen,int32 len)
{
	tchar disp[len * 2 + 1];

	memset(disp, 0x00, sizeof(disp));
	byteArrayToHexString (disp, tag, tagLen);

	printf("TAG:0x%s\r\n", disp);
	printf("LENGTH:%d\r\n------------------------------------------\r\n", len);

	return 0;
}



int main(int argc, char *argv[])
{
//	cstring tlvHexString = "E05A9F020600000000500082025C009F360200019F260886087FD3A9FE6FB49F100706010A03A010009F3303E0F0C09F1A0200365F2A0200369F1E08424B00081905CB9F950500000080009A030809229C01009F37041035EA1F8A00";
	cstring tlvHexString = "9F2608973E3A881FB73A6F9F2701809F100706010A03A4A0029F3704C620644D9F36020037950500000080009A031306149C01009F02060000000100005F2A02005182027C009F1A0200519F03060000000000009F3303E0E1C89F34034103029F0902008C9F4104000010585F3401014F07A0000000031010";
	
	cstring tlHexString = "9F26089F27019F10079F37049F360295059A039C019F02065F2A0282029F1A029F03069F33039F34039F09029F41045F34014F07";

	byte data[512];
	int32 len = 0;
	int32 ret = 0;

	ret = hexStringToByteArray (data, &len, tlvHexString);
	
	printf("TLVconvert ret = %d\r\n--------------------------------------------------------\r\n", ret);
	ret = decodeConstructedTlvData(saveTLVData, data, len, false);
	printf("ret = %d\r\n", ret);


	ret = hexStringToByteArray (data, &len, tlHexString);
	
	printf("TLconvert ret = %d\r\n--------------------------------------------------------\r\n", ret);
	ret = decodeConstructedTlvData(saveTLData, data, len, true);
	printf("ret = %d\r\n", ret);
	return 0;
}

