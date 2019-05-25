#ifndef LIB_THREAD_H
#define LIB_THREAD_H

#include "libtype.h"

#if (defined(WIN32) || defined(WIN64))
typedef HANDLE LIBTHREADHANDLE;
#else
typedef pthread_t LIBTHREADHANDLE;
#endif // WIN32 

typedef struct tagSThreadAttr
{

} SThreadAttr;

#if (defined(WIN32) || defined(WIN64))
typedef unsigned int (WINAPI *PFThrdProc)(void *);
#define LIBTHREAD_DECLARE(x)  unsigned int WINAPI  x
#define LIBTHREAD_RETURN(x)   return x;
#else
typedef void *  (*PFThrdProc)(void *);
#define LIBTHREAD_DECLARE(x)  void *  x
#define LIBTHREAD_RETURN(x)   return x;
#endif // 


INT32  LibThreadWait(LIBTHREADHANDLE handle);

void  LibThreadCloseHandle(LIBTHREADHANDLE handle);

void  LibThreadTerminate(LIBTHREADHANDLE handle);

void  LibThreadSuspend(LIBTHREADHANDLE handle);

void  LibThreadResume(LIBTHREADHANDLE handle);

void  LibSetThreadAttr(LIBTHREADHANDLE,SThreadAttr * pAttr);

void  LibThreadExit();

SThreadAttr*  LibGetThreadAttr(LIBTHREADHANDLE);

class CLibThread
{

public:
    CLibThread();
    virtual ~CLibThread();

	BOOL Start(PFThrdProc pthrdProc, void * pArg, BOOL bSuspend = false);

    BOOL  Start(BOOL bSuspend = FALSE);

    virtual void  OnTerminated()
    {
    }

	virtual void Stop();

    void  Suspend();

    void  Resume();

    void  SetAttribute(SThreadAttr *pAttr);

    SThreadAttr*  GetAttribute();

	BOOL  IsStart()
	{
		return m_bStart;
	}

	LIBTHREADHANDLE GetThreadHandle()
	{
		return m_oThreadhandle;
	}

private:
	void  Wait();

	void  Terminate();

protected:
    virtual void  ThrdProc()
    {
    }
protected:

    static LIBTHREAD_DECLARE(LibThreadFunc) (void* pArg); 
    CLibThread (const CLibThread&);
    CLibThread& operator = (const CLibThread&);

    BOOL				m_bStart;
    LIBTHREADHANDLE		m_oThreadhandle;
};

#endif



