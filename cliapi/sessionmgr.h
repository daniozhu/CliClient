#ifndef SESSION_MGR_H
#define SESSION_MGR_H

#include "singleton.h"
#include "cliapihelper.h"
#include "libmutex.h"

#include <vector>
#include <list>

class CTcpSocket;

class CSessionMgr
{
public:
	CSessionMgr();
	~CSessionMgr();

	DECLARE_SINGLETON(CSessionMgr);

	BOOL Init();
	void Uninit();

	HANDLE NewClient();

	void ClientJoin(HANDLE hHandle);

	void DeleteClient(HANDLE hHandle);

	BOOL SetSvrAddr(HANDLE hHandle, char* pchSvrAddr, UINT16 wPort);

	BOOL Process();

private:
	std::vector<CTcpSocket*>   m_vSockConnections;	
	CLibMutex m_oMutexConn;
};

#endif