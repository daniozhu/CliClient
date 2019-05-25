#include "clipktparser.h"
#include "libpkg.h"
#include "minilzo.h"
#include "tcpsocket.h"
#include "cliprocessor.h"

CCliPacketParser::CCliPacketParser()
{
	
}

CCliPacketParser::~CCliPacketParser()
{
}

INT32 CCliPacketParser::OnParsePacket(const CHAR *pBuf, UINT32 dwLen)
{
    if (dwLen < 2)
    {        
        return 0;//��Ҫ��������
    }

    if (pBuf[0] != '#')
    {
		return -1;
    }

	UINT32 dwRealLen = 1;
	while (dwRealLen < dwLen)
	{
		if (pBuf[dwRealLen] == ';')
		{
			return dwRealLen + 1;
		}

		dwRealLen++;
	}

    return 0;//��Ҫ��������
}

