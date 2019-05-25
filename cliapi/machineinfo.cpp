#include "machineinfo.h"

#if (defined(WIN32) || defined(WIN64))
//#include <WinSock2.h>

#include <rpcdce.h>
#include <IPTypes.h>
#include <IPHlpApi.h>
#include <assert.h>
//#include <Windows.h>

#pragma comment(lib, "rpcrt4")
#pragma comment(lib, "Iphlpapi")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <uuid/uuid.h>
#endif

BOOL g_bGetMac = FALSE;
std::string g_strMac;
CLibMutex   g_oGlobalMutex;

/* 网卡地址 */
#define MAX_MAC_ADDR_LEN                         17

/* 节点IP地址长度 */
#define MAX_IP_LEN                               16

void ResetMac()
{
	g_bGetMac = FALSE;
}

CHAR* FilterChar(CHAR* pszString, CHAR chFilterChar)
{
	if (NULL == pszString)
	{
		return pszString;
	}

	CHAR* pszCursor = NULL;
	CHAR* pszTmp = pszString;
	for (pszCursor = pszString; *pszCursor != 0x00; ++pszCursor)
	{
		if ((chFilterChar == 0x00 && isspace((UCHAR)(*pszCursor)))
			|| (chFilterChar != 0x00 && *pszCursor == chFilterChar))
		{
			continue;
		}

		*(pszTmp++) = *pszCursor;
	}

	*pszTmp = 0x00;

	return pszString;
}

#if !(defined(WIN32) || defined(WIN64))
#define MAXINTERFACES   16
BOOL GetMac(char *pszMac, int iMacSize, CTcpSocket* pTcpSocket)
{
	CAutoLock oAutoLock(&g_oGlobalMutex);
	if (g_bGetMac)
	{
		LibSnprintf(pszMac, iMacSize, "%s", g_strMac.c_str());
		return TRUE;
	}

	register int iSocket, iIntrface, iRetn = 0;
	struct ifreq  stIfreqInfo[MAXINTERFACES];
	struct arpreq stArpreqInfo;
	struct ifconf stIfconfInfo;

	if ((iSocket = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return FALSE;
	}

	stIfconfInfo.ifc_len = sizeof(stIfreqInfo);

	stIfconfInfo.ifc_buf = (caddr_t)stIfreqInfo;

	if (ioctl (iSocket, SIOCGIFCONF, (char*)&stIfconfInfo))
	{
		close(iSocket);
		return FALSE;
	}

	iIntrface = stIfconfInfo.ifc_len / sizeof(struct ifreq);
	while (iIntrface-- > 0)
	{
		if (ioctl(iSocket, SIOCGIFADDR, (char*)&stIfreqInfo[iIntrface]) == -1)
		{
			continue;
		}

		std::string strIpAddr = inet_ntoa(((struct sockaddr_in*)(&stIfreqInfo[iIntrface].ifr_addr))->sin_addr);

		char szIP[MAX_IP_LEN] = {0};

		GetLocalIp(pTcpSocket->GetSocket(), szIP, sizeof(szIP));

		if (strIpAddr != szIP)
		{
			continue;
		}

		if (ioctl(iSocket, SIOCGIFHWADDR, (char *) &stIfreqInfo[iIntrface]) == -1)
		{			
			continue;
		}

		//LibSnprintf(pszMac, iMacSize, "%02x:%02x:%02x:%02x:%02x:%02x",
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[0],
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[1],
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[2],
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[3],
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[4],
		//	(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[5]);
		LibSnprintf(pszMac, iMacSize, "%02x%02x%02x%02x%02x%02x",
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[0],
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[1],
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[2],
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[3],
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[4],
			(unsigned char)stIfreqInfo[iIntrface].ifr_hwaddr.sa_data[5]);
		break;
	}	

	g_strMac = pszMac;
	g_bGetMac = TRUE;
	return TRUE;
}
#else
BOOL GetMac(char *pszMac, int iMacSize, CTcpSocket* pTcpSocket)
{
	CAutoLock oAutoLock(&g_oGlobalMutex);

	if (g_bGetMac)
	{
		LibSnprintf(pszMac, iMacSize, "%s", g_strMac.c_str());
		return TRUE;
	}

	char macAddress[MAX_MAC_ADDR_LEN] = {0};
	PIP_ADAPTER_INFO pAdapaterInfo;
	DWORD dwAdapterInfoSize = 0;
	DWORD dwErr = GetAdaptersInfo(NULL, &dwAdapterInfoSize);
	if((dwErr != 0) && (dwErr != ERROR_BUFFER_OVERFLOW))
	{
		//获取网卡失败
		return FALSE;
	}

	pAdapaterInfo = new IP_ADAPTER_INFO[dwAdapterInfoSize];
	if (NULL == pAdapaterInfo)
	{
		//分配内存失败
		return FALSE;
	}
	if (GetAdaptersInfo(pAdapaterInfo, &dwAdapterInfoSize) != 0)
	{
		//获得网卡信息失败
		delete[] pAdapaterInfo;
		return FALSE;
	}

	//根据ip，从网卡信息中得到匹配的mac地址
	char ip[MAX_IP_LEN]={0};
	GetLocalIp(pTcpSocket->GetSocket(), ip, sizeof(ip));
	BOOL hit = FALSE;

	PIP_ADAPTER_INFO pCpyAdapterInfo = pAdapaterInfo;
	if(pCpyAdapterInfo != NULL)
	{
		do 
		{
			//_snprintf(macAddress, MAX_MAC_ADDR_LEN, "%02X%02X%02X%02X%02X%02X%02X%02X",
			//	pCpyAdapterInfo->Address[0],
			//	pCpyAdapterInfo->Address[1],
			//	pCpyAdapterInfo->Address[2],
			//	pCpyAdapterInfo->Address[3],
			//	pCpyAdapterInfo->Address[4],
			//	pCpyAdapterInfo->Address[5],
			//	pCpyAdapterInfo->Address[6],
			//	pCpyAdapterInfo->Address[7]);
			_snprintf(macAddress, MAX_MAC_ADDR_LEN, "%02X%02X%02X%02X%02X%02X",
				pCpyAdapterInfo->Address[0],
				pCpyAdapterInfo->Address[1],
				pCpyAdapterInfo->Address[2],
				pCpyAdapterInfo->Address[3],
				pCpyAdapterInfo->Address[4],
				pCpyAdapterInfo->Address[5]);

			PIP_ADDR_STRING pAddressList = &(pCpyAdapterInfo->IpAddressList);
			do 
			{
				int result;
				if((result=strncmp(ip, pAddressList->IpAddress.String, 4*4)) == 0)
				{
					hit = TRUE;
					break;
				}
				pAddressList = pAddressList->Next;
			} while (pAddressList != NULL);

			if(hit)
			{
				break;
			}
			pCpyAdapterInfo = pCpyAdapterInfo->Next;
		} while (pCpyAdapterInfo != NULL);
	}
	LibSnprintf(pszMac, iMacSize, "%s", macAddress);

	delete[] pAdapaterInfo;

	g_strMac = pszMac;
	g_bGetMac = TRUE;

	return TRUE;
}
#endif

BOOL GetClientName(char* pchClientInfo, int iSize, CTcpSocket* pTcpSocket)
{
	char szHostName[256] = {0};
	gethostname(szHostName, 256);
	
	LibSnprintf(pchClientInfo, iSize, "%s", szHostName);

	return TRUE;
}

BOOL GetHDID(char *p_pszHdid, int p_iHdidSize)
{
	return TRUE;
}
BOOL GetTermCode(char *p_pszTermCode, int p_iTermCodeSize)
{
	return TRUE;
}

BOOL GetLocalIp(sockfd fd, char *p_pszIpAddr, int p_iIpAddr)
{
	struct sockaddr_in guest;
#if (defined(WIN32) || defined(WIN64))
	int guestLen = sizeof(guest);
#else 
	socklen_t guestLen = sizeof(guest);
#endif

	getsockname(fd, (struct sockaddr*)&guest, &guestLen);
	LibSnprintf(p_pszIpAddr, p_iIpAddr, "%s", inet_ntoa(guest.sin_addr));
	return TRUE;
}