#include "StdAfx.h"
#include "commonlib.h"
#include <stdio.h>
#include <string.h>

CommonLib::CommonLib(void)
{
}

char* CommonLib::LibStrSafeCpy( char *strDestination, size_t numberOfElements, const char *strSource )
{
	if (numberOfElements  < strlen(strSource) +1)
	{
		return NULL;
	}

	return strncpy(strDestination, strSource, strlen(strSource) +1);
}

void CommonLib::LibNStrCpFromMStr(char* pchDest, size_t dwDestSize, String^ strSource)
{
	if (strSource == String::Empty)
	{
		pchDest[0] = 0;
		return;
	}

	char* pchBuf = (char*)(void*)Marshal::StringToHGlobalAnsi(strSource);

	LibStrSafeCpy(pchDest, dwDestSize, pchBuf);

	Marshal::FreeHGlobal((IntPtr)pchBuf);
}

void CommonLib::LibMCharToNChar(char* pchDest, Char sourceChar)
{
	char* pchBuf = (char*)(void*)Marshal::StringToHGlobalAnsi(sourceChar.ToString());

	*pchDest = pchBuf[0];

	Marshal::FreeHGlobal((IntPtr)pchBuf);		
}

void CommonLib::LibNDataCpFromMData(UINT8* pbyData, Int32 iDataLen, array<Byte>^ arrByte)
{
	Int32 iLen = iDataLen > arrByte->Length ? arrByte->Length : iDataLen;

	Marshal::Copy(arrByte, 0, (IntPtr)pbyData, iLen);
}

void CommonLib::LibMDataCpFromNData(array<Byte>^ arrByte, UINT8* pbyData, Int32 iDataLen)
{
	Int32 iLen = iDataLen > arrByte->Length ? arrByte->Length : iDataLen;

	Marshal::Copy((IntPtr)pbyData, arrByte, 0, iLen);
}
