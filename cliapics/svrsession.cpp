#include "stdafx.h"
#include "svrsession.h"
#include <gcroot.h>
#include "commonlib.h"
#include "cliapics.h"

using namespace System::Text;

namespace CliApiCS
{
	SvrSession::SvrSession(void)
	{
		
	}

	void SvrSession::OnConnected()
	{
		if (CliApi::s_dlgtOnConnected != nullptr)
		{
			CliApi::s_dlgtOnConnected();
		}
	}

	void SvrSession::OnTerminated()
	{
		if (CliApi::s_dlgtOnDisConnected != nullptr)
		{
			CliApi::s_dlgtOnDisConnected();
		}
	}

	void SvrSession::OnErrorInfo(INT32 iModuleErr, INT32 iSysErr)
	{
		if (CliApi::s_dlgtOnErrorInfo != nullptr)
		{
			CliApi::s_dlgtOnErrorInfo(iModuleErr, iSysErr);
		}
	}

	void SvrSession::OnMsgCallBack(char* pchMsg)
	{
		if (CliApi::s_dlgtOnMsgCallBack != nullptr)
		{
			String^ strMsg = Marshal::PtrToStringAnsi((IntPtr)pchMsg);

			CliApi::s_dlgtOnMsgCallBack(strMsg);
		}
	}

	void SvrSession::OnNotifyMsgNtf(const char* pchMsg, UINT32 dwLen)
	{
		if (CliApi::s_dlgtOnNotifyMsgNtf != nullptr)
		{
            // = Marshal::PtrToStringAnsi((IntPtr)(char*)pchMsg, (int)dwLen);
            array<Byte>^ bytes = Encoding::Unicode->GetBytes(Marshal::PtrToStringUni((IntPtr)(char*)pchMsg));
            String^ strMsg = Encoding::UTF8->GetString(bytes);

			CliApi::s_dlgtOnNotifyMsgNtf(strMsg);
		}
	}

	UInt16 SvrSession::SendToSvrMsg(String^ strMsg)
	{
		UInt32 dwSendLen = strMsg->Length;

		char szSendMsg[1024 * 1024] = { 0 };

		CommonLib::LibNStrCpFromMStr(szSendMsg
			, sizeof(szSendMsg)
			, strMsg);

		UINT32 sendID = 0;

		return ::SendMsg(szSendMsg, dwSendLen, m_hSvrHandle, &sendID);
	}

	HANDLE SvrSession::GetSvrHandle()
	{
		return m_hSvrHandle;
	}

	void SvrSession::SetSvrHandle(HANDLE hHandle)
	{
		m_hSvrHandle = hHandle;
	}
}