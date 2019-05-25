#ifndef EVENT_THREAD_H
#define EVENT_THREAD_H

#include "singleton.h"
#include "libthread.h"
#include "libtype.h"

//////////////////////////////////////////////////////////////////////////

class CTCPThread : public CLibThread
{
	CTCPThread(void);
	virtual ~CTCPThread(void);
	DECLARE_SINGLETON(CTCPThread)

public:
    virtual void ThrdProc();
    virtual void OnTerminated();

	BOOL LIBAPI Init();
	void LIBAPI Uninit();	
};

#endif

