#ifndef LIB_PKG_H
#define LIB_PKG_H

#include "libtype.h"

#pragma pack(push, 1)

struct SComMsgHeader
{
	UINT16    wProID;          //协议ID
	UINT32    dwBodyLen;       //消息体的长度
	UINT32    dwTransID;       //事务ID
	UINT64    qwTimsStamp;     //时间戳
	UINT8     byZip : 1;       //是否压缩  
	UINT8     byEncrypt : 7;   //加密类型
};

struct SNetMsgHeader
{
	SComMsgHeader	stComMsgHeader;

	UINT8			byReserve[100 - sizeof(SComMsgHeader)];   //保留字段
};

struct SEncrptHeader
{
	UINT32    dwBodyLen;
};

#pragma pack(pop)

#endif

