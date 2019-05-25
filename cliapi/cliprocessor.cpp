#include "cliprocessor.h"
#include "tcpsocket.h"
#include "errdefs.h"
#include "notifymsg.h"
#include "clipktparser.h"

extern PFNCB_NotifyMsgNtf				s_pfnNotifyMsgNtf;

inline std::string   LibInetNtoa(LONG lIp)
{
	struct in_addr addr;
#if (defined(WIN32) || defined(WIN64))
	addr.S_un.S_addr = lIp;
#else
	addr.s_addr = lIp;
#endif
	std::string strIp = inet_ntoa(addr);
	return strIp;
}

void CCliProcessor::OnNotifyMsgNtf(const char* pBody, UINT32 dwLen, CTcpSocket* pTcpSocket)
{
    if (s_pfnNotifyMsgNtf)
    {
		s_pfnNotifyMsgNtf(pBody, dwLen, (HANDLE)pTcpSocket);
    }
}

IMPLEMENT_SINGLETON(CCliProcessor);

CCliProcessor::CCliProcessor()
{
	m_funcOnConnected = NULL;
	m_pfnOnTerminated = NULL;
	m_pfnOnErrorInfo = NULL;
	m_pfnNotifyMsg = NULL;
}

CCliProcessor::~CCliProcessor()
{
	
}

bool CCliProcessor::Init()
{
	for (INT32 iPos = 0; iPos < MAX_PROTO_NUM; ++iPos)
	{
		m_afProcessFunc[iPos] = NULL;
	}

	return true;
}

void CCliProcessor::Uninit()
{
	CCliProcessor::DestroyInstance();
}

PPROCESSFUNC CCliProcessor::FindFunc(UINT16 wProID)
{
	return m_afProcessFunc[wProID];
}

void CCliProcessor::AddCommand(UINT16 wProID, PPROCESSFUNC pFunc)
{
	if (m_afProcessFunc[wProID] != NULL)
	{
		//这里可以打印日志
	}

	m_afProcessFunc[wProID] = pFunc;
}

PFuncCliOnConnected CCliProcessor::GetMDOnConnectFunc()
{
	return m_funcOnConnected;
}

void CCliProcessor::SetConnectedFunc(PFuncCliOnConnected pfnConnected)
{
	m_funcOnConnected = pfnConnected;
}


PFNCliOnTerminated CCliProcessor::GetOnTerminatedFunc()
{
	return m_pfnOnTerminated;
}

void CCliProcessor::SetOnTerminatedFunc(PFNCliOnTerminated pfnOnTerminated)
{
	m_pfnOnTerminated = pfnOnTerminated;
}

PFNCliOnErrorInfo CCliProcessor::GetOnErrorInfo()
{
	return m_pfnOnErrorInfo;
}

void CCliProcessor::SetOnErrorInfo(PFNCliOnErrorInfo pfnOnErrorInfo)
{
	m_pfnOnErrorInfo = pfnOnErrorInfo;
}

PFNCliNotifyMsg CCliProcessor::GetMsgCallBack()
{
	return m_pfnNotifyMsg;
}

void CCliProcessor::SetMsgCallBack(PFNCliNotifyMsg pfnNotifyMsg)
{
	m_pfnNotifyMsg = pfnNotifyMsg;
}