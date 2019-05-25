#pragma once

#include <gcroot.h>
#include "libtype.h"

using namespace System;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;

class CAutoLockHelper
{
public:
	CAutoLockHelper(gcroot<Object^> objLock)
	{
		m_lock = objLock;
		Monitor::Enter(m_lock);
	}

	~CAutoLockHelper()
	{
		Monitor::Exit(m_lock);
	}

	gcroot<Object^> m_lock;
};

ref class CommonLib
{
public:
	CommonLib(void);

	static char* LibStrSafeCpy(char *strDestination, size_t numberOfElements, const char *strSource);

	static void LibNStrCpFromMStr(char* pchDest, size_t dwDestSize, String^ strSource);

	static void LibMCharToNChar(char* pchDest, Char sourceChar);

	static void LibNDataCpFromMData(UINT8* pbyData, Int32 iDataLen, array<Byte>^ arrByte);

	static void LibMDataCpFromNData(array<Byte>^ arrByte, UINT8* pbyData, Int32 iDataLen);
};

