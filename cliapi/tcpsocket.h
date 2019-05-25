
#ifndef __TCPSOCKET_INCLUDE_H__
#define __TCPSOCKET_INCLUDE_H__

#if (defined(WIN32) || defined(WIN64))
#include <WinSock2.h>
#include <Windows.h>
#define sockfd SOCKET      
#else
#define sockfd int   
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#endif

#include "libtype.h"
#include "clipktparser.h"
#include "singleton.h"
#include "libmutex.h"
#include "cliapihelper.h"
#include "libdes.h"
#include <set>

#pragma pack(push, 1)

typedef struct tagSDesKey
{
	LibDESBlock		m_desKey;
	LibDESContext	m_desKeySche;
}SDesKey;

#pragma pack(pop)

inline UINT32 AlignUp(INT32 iData, UINT32 dwBytes)
{
	return ((iData) + (dwBytes) - 1) & (~(dwBytes - 1));
}

const INT32 MAX_BUF_LEN = 2097152;//2M

const INT32 MAX_TOTAL_BUF_LEN = 52428800;//50M


enum ESocketError
{
	ESE_RECV_FAILED	  = 1,
	ESE_SEND_FAILED	  = 2,
	ESE_CONN_FAILED   = 3,
	ESE_PKG_INVALID	  = 4,
	ESE_SEND_OVERFLOW = 5,
	ESE_RECV_OVERFLOW = 6,
};

class CTcpSocket
{
public:
	CTcpSocket();

	~CTcpSocket();

	bool ZipProto(UINT32 dwProtoID, INT32 iLen);
	
	bool RecvProcess(INT32 iCount = 5);

	bool SendProcess(INT32 iCount = 5);

	// 关闭连接函数
	void Close();

	// 发送函数
	INT32 Send(const char* pData, UINT32 dwLen);

	// 获取连接状态
	bool IsConnected();

	//设置负载均衡服务器IP
	void SetSvrAddr(const CHAR* pchBSIP, UINT16 wPort);

	//设置用户名和密码
	void SetUserInfo(const CHAR* pchBSIP, const CHAR* pchPwd);

	//设置交易网关服务器IP
	void SetGateSvrAddr(const CHAR* pchGTIP, UINT16 wPort);

	BOOL Init();

	void Uninit();

	void SetAutoConnect(bool bAutoConnect);

	sockfd GetSocket();

	void OnRecv(const CHAR* pchBuf, UINT32 dwLen);

	void OnConnect();

	void OnClose();

	void OnError(INT32 iModuleErr, INT32 iSysErr);

	void SetDeleted(BOOL bDeleted)
	{
		m_bDeleted = bDeleted;
	}

	BOOL IsDeleted()
	{
		return m_bDeleted;
	}

	UINT32 GetSendID()
	{		
		return (UINT32)InterlockedIncrement((LONG*)&m_dwSendID);
	}

private:
	// 设置为非阻塞
	void  SetNonblock();

	// 重连
	bool  ReConnect();

	// 是否可读
	bool IsReadable();

	// 是否可写
	bool IsWriteable();

	//读数据
	bool TCPRead(INT32 iCount);

	//发送数据
	bool TCPWrite(INT32 iCount);

	bool TCPConnect()
	{
		return m_bConnected;
	}

private:
	std::string			m_strGTSvrIP;
	UINT16				m_wGTSvrPort;
	sockfd				m_socket;
	std::string			m_strBlanceSvrIP;
	UINT16				m_wBlanceSvrPort;
	bool				m_bConnected;
	bool				m_bAutoReconnect;
	UCHAR				m_byRecvBuf[MAX_TOTAL_BUF_LEN];
	INT32				m_iRecvLen;
	UCHAR				m_bySendBuf[MAX_TOTAL_BUF_LEN];
	INT32				m_iSendLen;	
	CLibMutex           m_sendMutex;
	UINT32				m_dwLastUpdate;
	INT32               m_iTimer;
	BOOL                m_bDeleted;
	UINT32              m_dwSendID;
	
	static CCliPacketParser		m_oMsgHandler;

#if (defined(WIN32) || defined(WIN64))
	WSAData             m_wsa;
#endif

};

#endif // __ADTCPSOCKET_INCLUDE_H__
