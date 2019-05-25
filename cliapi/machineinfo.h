#ifndef MACHINE_INFO_H
#define MACHINE_INFO_H

#include "libtype.h"
#include "tcpsocket.h"
#include "libmutex.h"
#include "libstring.h"

extern BOOL				g_bGetMac ;
extern std::string		g_strMac;
extern CLibMutex		g_oGlobalMutex;

class CAutoLock
{
public:
	CAutoLock(CLibMutex* pMutex)
	{
		m_pLibMutex = pMutex;
		m_pLibMutex->Lock();
	};

	~CAutoLock()
	{
		m_pLibMutex->Unlock();
	}

public:
	CLibMutex*  m_pLibMutex;
};

void	ResetMac();

BOOL	GetLocalIp(char *, int);

CHAR*	FilterChar(CHAR* pszString, CHAR chFilterChar);

BOOL	GetMac(char *pszMac, int iMacSize, CTcpSocket* pTcpSocket);

BOOL	GetClientName(char* pchClientInfo, int iSize, CTcpSocket* pTcpSocket);

BOOL	GetHDID(char *p_pszHdid, int p_iHdidSize);

BOOL	GetTermCode(char *p_pszTermCode, int p_iTermCodeSize);

BOOL	GetLocalIp(sockfd fd, char *p_pszIpAddr, int p_iIpAddr);

#endif