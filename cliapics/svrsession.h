#pragma once

#include "cliapihelper.h"

namespace CliApiCS
{
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System;

	public ref class SvrSession
	{
	public:
		SvrSession(void);

		void OnConnected();

		void OnTerminated();

		void OnErrorInfo(INT32 iModuleErr, INT32 iSysErr);

		void OnMsgCallBack(char* pchMsg);

        void OnNotifyMsgNtf(const char* pchMsg, UINT32 dwLen);

	public:
		UInt16 SendToSvrMsg(String^ strMsg);

	public:
		void SetSvrHandle(HANDLE hHandle);

		HANDLE GetSvrHandle();

	public:
		HANDLE  m_hSvrHandle;
	};

}