#include "stdafx.h"
#include "svrsessionmgr.h"

IMPLEMENT_SINGLETON(CSvrSessionMgr);

CSvrSessionMgr::CSvrSessionMgr(void)
{
}

CSvrSessionMgr::~CSvrSessionMgr(void)
{

}

BOOL CSvrSessionMgr::Init(char* pchIPAddr, UINT16 wPort)
{
	m_strIpAddr = pchIPAddr;

	m_wPort = wPort;

	if (!CliInitEnv())
	{
		return FALSE;
	}
	
	CliSetConnectedFunc(CSvrSessionMgr::OnConnected);
	CliSetTerminateFunc(CSvrSessionMgr::OnTerminated);
	CliSetOnErrorInfoFunc(CSvrSessionMgr::OnErrorInfo);
	CliSetMsgCallBack(CSvrSessionMgr::OnMsgCallBack);
	SetNotifyMsgNtf(CSvrSessionMgr::OnNotifyMsgNtf);

	CliStart();

	return TRUE;
}

void CSvrSessionMgr::Uninit()
{
	CliStop();

	CliUninitEnv();
}

BOOL CSvrSessionMgr::Start()
{
	HANDLE hSvrHandle = CliNewClient();
	if (NULL == hSvrHandle)
	{
		return FALSE;
	}

	m_oSvrSession = gcnew SvrSession();

	m_oSvrSession->SetSvrHandle(hSvrHandle);

	CliSetSvrAddr(m_oSvrSession->GetSvrHandle(), (char*)m_strIpAddr.c_str(), m_wPort);

	CliClientJoin(hSvrHandle);

	return TRUE;
}

void CSvrSessionMgr::OnConnected(HANDLE hHandle)
{
	if (CSvrSessionMgr::Instance()->GetSvrSession()->GetSvrHandle() == hHandle)
	{
		CSvrSessionMgr::Instance()->GetSvrSession()->OnConnected();
	}
}

void CSvrSessionMgr::OnTerminated(HANDLE hHandle)
{
	if (CSvrSessionMgr::Instance()->GetSvrSession()->GetSvrHandle() == hHandle)
	{
		CSvrSessionMgr::Instance()->GetSvrSession()->OnTerminated();
	}
}

void CSvrSessionMgr::OnErrorInfo(HANDLE hHandle, INT32 iModuleErr, INT32 iSysErr)
{
	if (CSvrSessionMgr::Instance()->GetSvrSession()->GetSvrHandle() == hHandle)
	{
		CSvrSessionMgr::Instance()->GetSvrSession()->OnErrorInfo(iModuleErr, iSysErr);
	}
}

void CSvrSessionMgr::OnMsgCallBack(HANDLE hHandle, char* pchMsg)
{
	if (CSvrSessionMgr::Instance()->GetSvrSession()->GetSvrHandle() == hHandle)
	{
		CSvrSessionMgr::Instance()->GetSvrSession()->OnMsgCallBack(pchMsg);
	}
}

void CSvrSessionMgr::OnNotifyMsgNtf(const char* pNtfMsg, UINT32 dwLen, HANDLE hHandle)
{
    if (CSvrSessionMgr::Instance()->GetSvrSession()->GetSvrHandle() == hHandle)
    {
        CSvrSessionMgr::Instance()->GetSvrSession()->OnNotifyMsgNtf(pNtfMsg, dwLen);
    }
}


gcroot<SvrSession^>& CSvrSessionMgr::GetSvrSession()
{
	return m_oSvrSession;
}

void CSvrSessionMgr::SetAddr(char* pchIPAddr, UINT16 wPort)
{
	m_strIpAddr = pchIPAddr;
	m_wPort = wPort;
}