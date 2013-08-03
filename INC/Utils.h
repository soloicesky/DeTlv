#ifndef _UTILS_H_
#define _UTILS_H_

#include <string.h>

#include "UserType.h"

#ifdef _cpluscplus
extern "C" {
#endif

#define VALIDATEHEXSTRING(s) ((strlen((s))%2)==0)?1:0 //�ж��Ƿ��ǺϷ������ֽ�����ת��������ʮ�������ַ���

#define UPERCASE(c) ((c)>='a' && (c)<='z')?((c)-0x20):(c)  //ת��д

#define LOWECASE(c)	 ((c)>='a' && (c)<='z')?((c)+0x20):(c) //תСд

#define DECCHECK(c)	((c)>='0' && (c) <= '9')			//ʮ�����ַ�?

#define HEXCHECK(c)	 (((c)>='0' && (c) <= '9') || ((c)>='a' && (c) <= 'f') || ((c)>='A' && (c) <= 'F'))  	//ʮ�������ַ�?


int32 toUperCase(cstring str);

int32 toLowerCase(cstring str);

inline int32 getCharIndex(cstring str, tchar ch);

int32 hexStringToByteArray(byteArray desBytearray, int32 *byteArrayLen, cstring hexString);

int32 byteArrayToHexString(cstring desHexString, byteArray srcByteArray, int32 srcByteArrayLen);


#ifdef _cpluscplus
}
#endif

#endif

