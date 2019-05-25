#ifndef LIB_PKG_H
#define LIB_PKG_H

#include "libtype.h"

#pragma pack(push, 1)

struct SComMsgHeader
{
	UINT16    wProID;          //Э��ID
	UINT32    dwBodyLen;       //��Ϣ��ĳ���
	UINT32    dwTransID;       //����ID
	UINT64    qwTimsStamp;     //ʱ���
	UINT8     byZip : 1;       //�Ƿ�ѹ��  
	UINT8     byEncrypt : 7;   //��������
};

struct SNetMsgHeader
{
	SComMsgHeader	stComMsgHeader;

	UINT8			byReserve[100 - sizeof(SComMsgHeader)];   //�����ֶ�
};

struct SEncrptHeader
{
	UINT32    dwBodyLen;
};

#pragma pack(pop)

#endif

