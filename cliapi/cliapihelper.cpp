#include "cliapihelper.h"
#include "tcpsocket.h"
#include "tcpthread.h"
#include "clipktparser.h"
#include "cliprocessor.h"
#include "libstring.h"
#include <time.h>
#include "sessionmgr.h"
#include "machineinfo.h"

#pragma  warning(disable : 4482)

CLIAPI BOOL CLI_STDCALL CliInitEnv()
{
	srand((unsigned)time(NULL));

	CSessionMgr::CreateInstance();
	CTCPThread::CreateInstance();
	CCliProcessor::CreateInstance();

	if (!CSessionMgr::Instance()->Init())
	{
		return FALSE;
	}

	if (!CCliProcessor::Instance()->Init())
	{
		return FALSE;
	}

	if (!CTCPThread::Instance()->Init())
	{
		return FALSE;
	}

	return TRUE;
}

CLIAPI HANDLE CLI_STDCALL CliNewClient()
{
	return CSessionMgr::Instance()->NewClient();
}

CLIAPI void CLI_STDCALL CliSetSvrAddr(HANDLE hHandle, CHAR* pchBuf, UINT16 wPort)
{
	CSessionMgr::Instance()->SetSvrAddr(hHandle, pchBuf, wPort);	
}

CLIAPI void CLI_STDCALL CliClientJoin(HANDLE hHandle)
{
	CSessionMgr::Instance()->ClientJoin(hHandle);
}

CLIAPI BOOL CLI_STDCALL CliStart()
{
	return CTCPThread::Instance()->Start();
}

CLIAPI void CLI_STDCALL CliClose(HANDLE hHandle)
{
	CSessionMgr::Instance()->DeleteClient(hHandle);
}

CLIAPI void CLI_STDCALL CliStop()
{	
	if (CTCPThread::Instance())
	{
		CTCPThread::Instance()->Stop();
	}
}

CLIAPI void CLI_STDCALL CliUninitEnv()
{
	if (CTCPThread::Instance())
	{
		CTCPThread::Instance()->Uninit();
	}	

	if (CCliProcessor::Instance())
	{
		CCliProcessor::Instance()->Uninit();
	}

	if (CSessionMgr::Instance())
	{
		CSessionMgr::Instance()->Uninit();
	}
}

CLIAPI void CLI_STDCALL CliSetConnectedFunc(PFuncCliOnConnected pfnConnected)
{
	CCliProcessor::Instance()->SetConnectedFunc(pfnConnected);
}

CLIAPI void CLI_STDCALL CliSetTerminateFunc(PFNCliOnTerminated pfnOnTerminate)
{
	CCliProcessor::Instance()->SetOnTerminatedFunc(pfnOnTerminate);
}

CLIAPI void CLI_STDCALL CliSetOnErrorInfoFunc(PFNCliOnErrorInfo pfnOnErrorInfo)
{
	CCliProcessor::Instance()->SetOnErrorInfo(pfnOnErrorInfo);
}

CLIAPI void CLI_STDCALL CliSetMsgCallBack(PFNCliNotifyMsg pfnNotifyMsg)
{
	CCliProcessor::Instance()->SetMsgCallBack(pfnNotifyMsg);
}

//////////////////////////////////////////////////////////////////////////
PFNCB_NotifyMsgNtf s_pfnNotifyMsgNtf = nullptr;

CLIAPI void CLI_STDCALL SetNotifyMsgNtf(PFNCB_NotifyMsgNtf pfnNotifyMsgNtf)
{
	s_pfnNotifyMsgNtf = pfnNotifyMsgNtf;
}

CLIAPI UINT16 CLI_STDCALL SendMsg(const char* pSendMsg, UINT32 dwSendMsgLen, HANDLE hHandle, UINT32* pdwSendID)
{
	if (NULL == hHandle)
	{
		return ErrNetRlt_Failed_Handle_NULL;
	}

	CTcpSocket* pTcpSocket = (CTcpSocket*)hHandle;

	UINT32 dwSendID = pTcpSocket->GetSendID();

	if (pdwSendID != NULL)
	{
		*pdwSendID = dwSendID;
	}

	return pTcpSocket->Send(pSendMsg, dwSendMsgLen);
}