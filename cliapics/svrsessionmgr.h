#pragma once

#include "singleton.h"
#include "cliapihelper.h"
#include "svrsession.h"

#include <gcroot.h>

using namespace CliApiCS;

class CSvrSessionMgr
{
public:
	CSvrSessionMgr(void);
	~CSvrSessionMgr(void);

	DECLARE_SINGLETON(CSvrSessionMgr);

	BOOL Init(char* pchIPAddr, UINT16 wPort);

	void Uninit();

	BOOL Start();

	static void OnConnected(HANDLE hHandle);

	static void OnTerminated(HANDLE hHandle);

	static void OnErrorInfo(HANDLE hHandle, INT32 iModuleErr, INT32 iSysErr);

	static void OnMsgCallBack(HANDLE hHandle, char* pchMsg);

    static void OnNotifyMsgNtf(const char* pNtfMsg, UINT32 dwLen, HANDLE hHandle);

	gcroot<SvrSession^>& GetSvrSession();

	void SetAddr(char* pchIPAddr, UINT16 wPort);

private:
	gcroot<SvrSession^> m_oSvrSession;

	std::string         m_strIpAddr;
	UINT16              m_wPort;
};

