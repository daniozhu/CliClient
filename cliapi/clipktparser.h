#ifndef CLI_PKT_PARSER_H
#define CLI_PKT_PARSER_H

#include "libtype.h"
#include "parsepacket.h"


class CCliPacketParser : public ISocketHandler
{
public:
    CCliPacketParser();
    ~CCliPacketParser();	

    virtual INT32 OnParsePacket(const CHAR* pBuf, UINT32 dwLen);

public:
};

#endif

