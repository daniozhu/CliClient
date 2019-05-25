#include "tcpsocket.h"
#include "clipktparser.h"
#include "libpkg.h"
#include "minilzo.h"
#include "cliprocessor.h"
#include "machineinfo.h"

#include <time.h>
//////////////////////////////////////////////////////////////////////////

#if (defined(WIN32) || defined(WIN64))
#include <WinSock2.h>
#define close        closesocket 

#define HT_EWOULDBLOCK  EWOULDBLOCK
#define HT_ECONNABORTED WSAECONNABORTED
#define HT_ECONNRESET   WSAECONNRESET
#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#define HT_EWOULDBLOCK      EAGAIN
#define WSAGetLastError() errno
#define INVALID_SOCKET    (-1)
#define SOCKET_ERROR      (-1)
#define HT_ECONNABORTED ECONNABORTED
#define HT_ECONNRESET   ECONNRESET

#endif

#define MAX_PROCESS_COUNT  1000

CCliPacketParser CTcpSocket::m_oMsgHandler;

CTcpSocket::CTcpSocket()
	: m_strGTSvrIP("")
	, m_wGTSvrPort(0)
	, m_socket(INVALID_SOCKET)
	, m_bConnected(false)
	, m_bAutoReconnect(true)
	, m_iRecvLen(0)
	, m_iSendLen(0)
	, m_dwLastUpdate(0)
	, m_iTimer(1000)
	, m_bDeleted(FALSE)
	, m_dwSendID(0)
{	
	memset(m_byRecvBuf, 0, MAX_TOTAL_BUF_LEN);
	memset(m_bySendBuf, 0, MAX_TOTAL_BUF_LEN);

	Init();
}

CTcpSocket::~CTcpSocket()
{
	m_socket = INVALID_SOCKET;
}

void CTcpSocket::Close()
{		
	//m_bAutoReconnect = false;
	m_bConnected = false;
	m_dwLastUpdate = 0;

	if (m_socket != INVALID_SOCKET)
	{
		close(m_socket);	
		m_socket = INVALID_SOCKET;

		OnClose();

		ResetMac();
	}
}

void CTcpSocket::OnConnect()
{
	PFuncCliOnConnected pfnMDOnConnected = CCliProcessor::Instance()->GetMDOnConnectFunc();
	if (pfnMDOnConnected != NULL)
	{
		pfnMDOnConnected((HANDLE)this);
	}
	
	//准备发送获取协议版本
	//SProVersionRpt stReport;
	//stReport.dwCurVersion = ProtoVersion;

	//Send((void*)&stReport, ID_ProVersionRpt);
}

void CTcpSocket::OnClose()
{
	PFNCliOnTerminated pfnOnTerminated = CCliProcessor::Instance()->GetOnTerminatedFunc();
	if (pfnOnTerminated != NULL)
	{
		pfnOnTerminated((HANDLE)this);
	}
}

void CTcpSocket::OnError(INT32 iModuleErr, INT32 iSysErr)
{
	PFNCliOnErrorInfo pfnOnErrorInfo = CCliProcessor::Instance()->GetOnErrorInfo();
	if (pfnOnErrorInfo != NULL)
	{
		pfnOnErrorInfo((HANDLE)this, iModuleErr, iSysErr);
	}
}

bool CTcpSocket::RecvProcess(INT32 iCount)
{	
	if (!m_bConnected)
	{
		if (!m_bAutoReconnect)
		{
			return false;
		}

		UINT32 dwNow = (UINT32)time(NULL);
		// 每3秒钟检查连接并进行重连
		if (dwNow - m_dwLastUpdate > 3)
		{
			m_dwLastUpdate = dwNow;
			ReConnect();
			return true;
		}
	}
	
	//读数据
	bool bBusy = TCPRead(iCount);	

	return bBusy;
}

bool CTcpSocket::SendProcess(INT32 iCount)
{
	bool bBusy = false;
	if (!m_bConnected)
	{
		return bBusy;
	}

	// 检查socket是否可写
	bBusy = TCPWrite(iCount);	

	return bBusy;
}

bool CTcpSocket::TCPRead(INT32 iCount)
{
	bool bBusy = false;
	// 检查socket是否可读，并做读操作
	while (IsReadable())
	{
		int iDataLen = MAX_TOTAL_BUF_LEN - m_iRecvLen;
		if (iDataLen <= 0)
		{
			return bBusy;
		}

		INT32 iReadLen = recv(m_socket, (char*)m_byRecvBuf + m_iRecvLen, iDataLen, 0);
		if (iReadLen == SOCKET_ERROR)
		{
			INT32 iLastErr = WSAGetLastError();
			if (iLastErr != HT_EWOULDBLOCK)
			{
				OnError(ESE_RECV_FAILED, iLastErr);
				if ((HT_ECONNABORTED == iLastErr) || (HT_ECONNRESET == iLastErr))
				{
					Close();
				}
			}

			break;
		}

		iCount--;
		bBusy = true;

		m_iRecvLen += iReadLen;

		UCHAR* pStart  = m_byRecvBuf;
		INT32 iLeftLen = m_iRecvLen;

		while (iLeftLen > 0)
		{
			INT32 iPkgLen = m_oMsgHandler.OnParsePacket((char*)pStart, iLeftLen);
			if (iPkgLen == -1)
			{
				// 错误包不解析，直接丢弃
				OnError(ESE_PKG_INVALID, 0);
				m_iRecvLen = 0;						
				break;
			}

			if (iPkgLen == 0 && iLeftLen < m_iRecvLen && iLeftLen != 0)
			{
				// 不完整包，去掉头部完整包的数据，继续收集
				memmove(m_byRecvBuf, pStart, iLeftLen);
				m_iRecvLen = iLeftLen;
				break;
			}

			//需要极继续接收
			if (iPkgLen == 0)
			{
				break;
			}

			// 完整包，通知App回调
			OnRecv((char*)pStart, iPkgLen);
			pStart += iPkgLen;
			iLeftLen -= iPkgLen;
		}

		if (iLeftLen == 0)
		{
			// 完整包都处理完了，快速清零
			m_iRecvLen = 0;					
		}

		if (iCount <= 0)
		{
			break;
		}
	}

	return bBusy;
}

bool CTcpSocket::TCPWrite(INT32 iCount)
{
	bool bBusy = false;	
	m_sendMutex.Lock();
	// 如果可写，而且发送buf不为空
	while (m_iSendLen > 0)
	{
		if (!IsWriteable())
		{
			m_sendMutex.Unlock();
			return bBusy;
		}

		INT32 iSendLen = send(m_socket, (char*)m_bySendBuf, m_iSendLen, 0);
		if (iSendLen == SOCKET_ERROR)
		{
			INT32 iLastErr = WSAGetLastError();
			if (HT_EWOULDBLOCK != iLastErr)
			{
				OnError(ESE_RECV_FAILED, iLastErr);
				if ((HT_ECONNABORTED == iLastErr) || (HT_ECONNRESET == iLastErr))
				{
					Close();
				}
			}
			break;
		}

		bBusy = true;

		if (iSendLen == m_iSendLen)
		{
			// 全部发送完了，快速清零
			m_iSendLen     = 0;
			m_bySendBuf[0] = 0;
			break;
		}

		// 只发送了一部分，则移除头部数据
		if (iSendLen != 0)
		{
			memmove(m_bySendBuf, m_bySendBuf + iSendLen, m_iSendLen - iSendLen);
			m_iSendLen -= iSendLen;
			m_bySendBuf[m_iSendLen] = 0;
		}
	}
	m_sendMutex.Unlock();
	return bBusy;
}

INT32 CTcpSocket::Send(const char* pData, UINT32 dwLen)
{
	if (!TCPConnect())
	{
		return ErrNetRlt_Failed_Not_Connect;
	}
	
	m_sendMutex.Lock();
	//如果可写，且待发送缓冲为空，直接发送
	if ((m_iSendLen == 0) && IsWriteable())
	{
		INT32 iSendLen = send(m_socket, pData, dwLen, 0);
		if (SOCKET_ERROR == iSendLen)
		{
			INT32 iLastErr = WSAGetLastError();
			if (HT_EWOULDBLOCK != iLastErr)
			{
				OnError(ESE_SEND_FAILED, iLastErr);
				if ((HT_ECONNABORTED == iLastErr) || (HT_ECONNRESET == iLastErr))
				{
					Close();
					m_sendMutex.Unlock();
					return ErrNetRlt_Failed_Conn_Err;
				}
			}
		}
		else if (iSendLen != (INT32)dwLen)
		{
			// 只发送了一部分，留待Update中继续发送.
			memcpy(m_bySendBuf + m_iSendLen, pData + iSendLen, dwLen - iSendLen);
			m_iSendLen += (dwLen - iSendLen);
			m_bySendBuf[m_iSendLen] = 0;
		}
	}	
	else
	{
		// 否则保存到发送缓冲
		if (m_iSendLen + dwLen >= MAX_TOTAL_BUF_LEN)
		{
			OnError(ESE_SEND_OVERFLOW, 0);

			m_sendMutex.Unlock();

			return ErrNetRlt_Failed_Overflow;
		}
		else
		{
			memcpy(m_bySendBuf + m_iSendLen, pData, dwLen);
			m_iSendLen += dwLen;
			m_bySendBuf[m_iSendLen] = 0;
		}		
	}
	m_sendMutex.Unlock();

	return ErrNetRlt_Succ;
}


bool CTcpSocket::IsConnected()
{
	// 通过判断是否可写,来判断是否处于连接状态
	return IsWriteable();
}

void CTcpSocket::SetSvrAddr(const CHAR* pchBSIP, UINT16 wPort)
{
	m_strBlanceSvrIP = pchBSIP;
	m_wBlanceSvrPort = wPort;

	m_strGTSvrIP = m_strBlanceSvrIP;
	m_wGTSvrPort = m_wBlanceSvrPort;
}

void CTcpSocket::SetGateSvrAddr(const CHAR* pchGTIP, UINT16 wPort)
{
	m_strGTSvrIP = pchGTIP;
	m_wGTSvrPort = wPort;
}

BOOL CTcpSocket::Init()
{
#if (defined(WIN32) || defined(WIN64))
	WSAStartup(MAKEWORD(2, 2), &m_wsa);
#endif

	if (lzo_init() != LZO_E_OK)
	{		
		return FALSE;
	}

	return TRUE;
}

void CTcpSocket::SetAutoConnect(bool bAutoConnect)
{
	m_bAutoReconnect = bAutoConnect;
}

void CTcpSocket::Uninit()
{
	Close();

#if (defined(WIN32) || defined(WIN64))
	WSACleanup();
#endif
}

void CTcpSocket::SetNonblock()
{
#if (defined(WIN32) || defined(WIN64))
	u_long nonblocking = 1;
	ioctlsocket(m_socket, FIONBIO, &nonblocking);
#else
	INT32 flags = fcntl(m_socket, F_GETFL, 0);
	fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);
#endif
}

bool CTcpSocket::ReConnect()
{
	if (m_socket != INVALID_SOCKET)
	{
		close(m_socket);
		m_bConnected = false;
		m_socket = INVALID_SOCKET;
	}

	UINT32 wErrCode;
	m_socket = socket(AF_INET, SOCK_STREAM, 0);	
	if (INVALID_SOCKET == m_socket)
	{
		wErrCode = WSAGetLastError();
		return false;
	}

    const CHAR szOptVal = 1;
    setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (const char *)&szOptVal, sizeof(szOptVal));

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(m_strGTSvrIP.c_str());
	server.sin_port = htons(m_wGTSvrPort);

	INT32 iRet = connect(m_socket, (sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR  == iRet)
	{
		OnError(ESE_CONN_FAILED, WSAGetLastError());

		return false;
	}

	//正常连接后，设置为非阻塞状态
	SetNonblock();

	m_bConnected   = true;

	OnConnect();

	return true;
}

bool CTcpSocket::IsReadable()
{
	if (!m_bConnected)
	{
		return false;
	}

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(m_socket, &readfds);

	timeval time = {0, 0};

#if (defined(WIN32) || defined(WIN64))
	return select(1, &readfds, 0, 0, &time) != 0;
#else
	return  (select(m_socket + 1, 0, &readfds, 0, &time) != 0);
#endif
}

bool CTcpSocket::IsWriteable()
{
	if (!m_bConnected)
	{
		return false;
	}

	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(m_socket, &writefds);

	timeval time = {0, 0};

#if (defined(WIN32) || defined(WIN64))
	return  (select(1, 0, &writefds, 0, &time) != 0);
#else
	return  (select(m_socket + 1, 0, &writefds, 0, &time) != 0);
#endif
}

sockfd CTcpSocket::GetSocket()
{
	return m_socket;
}

void CTcpSocket::OnRecv(const CHAR* pchBuf, UINT32 dwLen)
{
	CCliProcessor::Instance()->OnNotifyMsgNtf(pchBuf, dwLen, this);
}