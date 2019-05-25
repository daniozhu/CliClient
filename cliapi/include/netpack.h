#ifndef NET_PACK_H
#define NET_PACK_H

#include <vector>
#include <string>
#include "libtype.h"

#if (defined(WIN32) || defined(WIN64))
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/resource.h>
#include <string.h>
#endif

using std::vector;

class CNetPack
{
public:
    CNetPack();
    virtual ~CNetPack();

    void  Init(CHAR *pNetData, INT32 iSize);
    void  Init(CHAR *pNetData, INT32 iSize, INT32 iType);
    void  Reset();

    CHAR* GetData(){ return m_pData; }
    INT32  GetDataLen(){ return m_iLen; }

    INT32 AddByte(UCHAR byByte);
    INT32 DelByte(UCHAR &byByte);

    INT32 AddChar(CHAR chChar);
    INT32 DelChar(CHAR &chChar);

    INT32 AddWord(UINT16 wWord);
    INT32 DelWord(UINT16 &wWord);

    INT32 AddShort(INT16 shShort);
    INT32 DelShort(INT16 &shShort);

    INT32 AddDword(UINT32 dwDword);
    INT32 DelDword(UINT32 &dwDword);

    INT32 AddInt(INT32 iInt);
    INT32 DelInt(INT32 &iInt);

    INT32 AddUint64(UINT64 qwUint64);
    INT32 DelUint64(UINT64& qwUint64);

    INT32 AddInt64(INT64 llInt64);
    INT32 DelInt64(INT64 &llInt64);

    INT32 AddFloat(FLOAT fFloat);
    INT32 DelFloat(FLOAT &fFloat);

    INT32 AddDouble(DOUBLE dbDouble);
    INT32 DelDouble(DOUBLE &dbDouble);

    INT32 AddString(const CHAR *pszString, INT32 iSize);
    INT32 DelString(CHAR *pszOut, INT32 iSize);

    INT32 Strnlen(const CHAR *pszString, INT32 iSize);

    INT32 AddBuf(const UCHAR* pbyBuf, INT32 iSize);
    INT32 DelBuf(UCHAR* pbyBuf, INT32 iSize);

protected:
    CHAR *	m_pData;  
    INT32	m_iSize; 
    INT32	m_iLen;  
    INT32	m_iType;  
};


class IProtocol 
{
public:
    virtual INT32 Encode(INT32 iMsgID, void *pHost, CHAR *pNet, INT32 iNetSize) = 0;
    virtual INT32 Decode(INT32 iMsgID, CHAR *pNet,INT32 iNetSize, void *pHost, INT32 iHostSize) = 0;
};

#endif 

