#include "tcpthread.h"
#include "tcpsocket.h"
#include "datetime.h"
#include "sessionmgr.h"

IMPLEMENT_SINGLETON(CTCPThread);

#define EVENT_TIMER_SLEEP_TIME 1  //休眠1毫秒

CTCPThread::CTCPThread(void)
{
}

CTCPThread::~CTCPThread(void)
{
}

BOOL LIBAPI CTCPThread::Init()
{
	return TRUE;
}

void LIBAPI CTCPThread::Uninit()
{
	Stop();

	CTCPThread::DestroyInstance();
}

#define DEFALUT_COUNT_FOR_SLEEP  10

void CTCPThread::ThrdProc()
{
    while(IsStart())
	{	
		BOOL bBusy = CSessionMgr::Instance()->Process();

		if (!bBusy)
		{
			//这个Sleep可以以后让客户设置
			LibSleep(1);
		}		
	}
}

void CTCPThread::OnTerminated()
{
}
