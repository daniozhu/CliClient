#include "sessionmgr.h"
#include "tcpsocket.h"

IMPLEMENT_SINGLETON(CSessionMgr);

CSessionMgr::CSessionMgr()
{

}

CSessionMgr::~CSessionMgr()
{

}


BOOL CSessionMgr::Init()
{
	return TRUE;
}

void CSessionMgr::Uninit()
{
	m_oMutexConn.Lock();
	for (std::vector<CTcpSocket*>::iterator itVec = m_vSockConnections.begin()
		; itVec != m_vSockConnections.end(); ++itVec)
	{
		if (*itVec == NULL)
		{
			continue;
		}

		delete (CTcpSocket*)(*itVec);
	}

	m_vSockConnections.clear();
	m_oMutexConn.Unlock();

	CSessionMgr::DestroyInstance();
}

HANDLE CSessionMgr::NewClient()
{
	CTcpSocket* pTcpSocket = new CTcpSocket();
	if (NULL == pTcpSocket)
	{
		return NULL;
	}

	pTcpSocket->SetAutoConnect(true);

	return (HANDLE)pTcpSocket;
}

void CSessionMgr::ClientJoin(HANDLE hHandle)
{
	CTcpSocket* pTcpSocket= (CTcpSocket*)hHandle;

	m_oMutexConn.Lock();
	BOOL bFind = FALSE;
	for (std::vector<CTcpSocket*>::iterator itVec = m_vSockConnections.begin();
		itVec != m_vSockConnections.end(); ++itVec)
	{
		if (pTcpSocket == *itVec)
		{
			bFind = TRUE;
			break;
		}
	}

	if (!bFind)
	{
		m_vSockConnections.push_back(pTcpSocket);
	}
	m_oMutexConn.Unlock();
}

void CSessionMgr::DeleteClient(HANDLE hHandle)
{
	if (NULL == hHandle)
	{
		return;
	}

	CTcpSocket* pTcpSocket = (CTcpSocket*)hHandle;

	pTcpSocket->SetDeleted(TRUE);
}

BOOL CSessionMgr::SetSvrAddr(HANDLE hHandle, char* pchSvrAddr, UINT16 wPort)
{
	CTcpSocket* pTcpSocket = (CTcpSocket*)hHandle;
	if (NULL == pTcpSocket)
	{
		return FALSE;
	}

	pTcpSocket->SetSvrAddr(pchSvrAddr, wPort);

	return TRUE;
}

BOOL CSessionMgr::Process()
{
	bool bBusy = false;
	std::vector<CTcpSocket*> vecSocks;

	m_oMutexConn.Lock();
	
	for (std::vector<CTcpSocket*>::iterator itVec = m_vSockConnections.begin()
		; itVec != m_vSockConnections.end(); ++itVec)
	{
		if ((*itVec)->IsDeleted())
		{
			(*itVec)->Close();
			delete *itVec;

			continue;
		}

		vecSocks.push_back(*itVec);
	}

	m_oMutexConn.Unlock();

	for (std::vector<CTcpSocket*>::iterator itVec = vecSocks.begin()
		; itVec != vecSocks.end(); ++itVec)
	{
		bBusy |= (*itVec)->RecvProcess();

		bBusy |= (*itVec)->SendProcess();
	}

	if (vecSocks.size() > 0)
	{
		vecSocks.clear();
	}	

	return bBusy;
}
