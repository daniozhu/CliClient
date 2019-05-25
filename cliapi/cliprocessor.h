#ifndef CLI_PROCESSOR_H
#define CLI_PROCESSOR_H

#include "singleton.h"
#include "cliapihelper.h"

#define MAX_PROTO_NUM  65536

class CTcpSocket;

typedef void (*PPROCESSFUNC)(void* pBody, CTcpSocket*);

class CCliProcessor
{
public:
	CCliProcessor();
	~CCliProcessor();

	DECLARE_SINGLETON(CCliProcessor);

	bool Init();
	void Uninit();

	PPROCESSFUNC FindFunc(UINT16);

	void AddCommand(UINT16 wProID, PPROCESSFUNC pFunc);

	PFuncCliOnConnected GetMDOnConnectFunc();	

	void SetConnectedFunc(PFuncCliOnConnected pfnConnected);

	PFNCliOnTerminated GetOnTerminatedFunc();

	void SetOnTerminatedFunc(PFNCliOnTerminated pfnOnTerminated);

	PFNCliOnErrorInfo GetOnErrorInfo();

	void SetOnErrorInfo(PFNCliOnErrorInfo pfnOnErrorInfo);

	PFNCliNotifyMsg GetMsgCallBack();

	void SetMsgCallBack(PFNCliNotifyMsg pfnNotifyMsg);

	void OnNotifyMsgNtf(const char* pBody, UINT32 dwLen, CTcpSocket* pTcpSocket);

public:
	PFuncCliOnConnected  m_funcOnConnected;
	PFNCliOnTerminated   m_pfnOnTerminated;
	PFNCliOnErrorInfo    m_pfnOnErrorInfo;
	PFNCliNotifyMsg      m_pfnNotifyMsg;
	PPROCESSFUNC		 m_afProcessFunc[MAX_PROTO_NUM];
};

#endif