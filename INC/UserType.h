#ifndef _USERTYPE_H_
#define _USERTYPE_H_

#ifdef _cplusplus
extern "C"
{
#endif

#define byte		unsigned char     //8bit 无符号数
#define tchar		char			  //8bit 无符号数

#define int16		short				//16bit 有符号数
#define uint16		unsigned short		//16bit 无符号数
#define int32		int					//32bit 有符号数
#define uint32		unsigned int		//32bit 无符号数
#define int64		long long				//64bit 有符号数
#define uint64		unsigned long long	//64bit 无符号数
	
#define cstring	    char*				//字符串
#define byteArray	byte*				//8bit 无符号数组

#define boolean	    byte				//布尔值
#define true		(1)					//真
#define false		(0)					//假


#ifdef _cplusplus
}
#endif

#endif

