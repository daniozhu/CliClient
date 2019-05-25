#ifndef CLI_API_HELPER_H
#define CLI_API_HELPER_H

#include "libtype.h"

#if (!(defined(WIN32) || defined(WIN64)))
typedef void* HANDLE;
#endif

#if defined(WIN32) || defined(WIN64)
#if defined(CLIAPI_EXPORTS)
#define CLIAPI __declspec(dllexport)
#else
#define CLIAPI __declspec(dllimport)
#endif
#define CLI_STDCALL __stdcall
#define CLI_EXPORTS __declspec(dllexport)
#else
#define CLIAPI
#define CLI_STDCALL
#define CLI_EXPORTS
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

typedef enum tagEErrNetRltInfo
{
	ErrNetRlt_Succ = 0,						//���ͳɹ�
	ErrNetRlt_Failed_Not_Connect = -1,		//ʧ�ܣ�û�����ӷ�����
	ErrNetRlt_Failed_Encode = -2,			//ʧ�ܣ��������
	ErrNetRlt_Failed_Zip = -3,				//ʧ�ܣ�ѹ��ʧ��
	ErrNetRlt_Failed_Conn_Err = -4,			//ʧ�ܣ�socket���Ӵ���
	ErrNetRlt_Failed_Overflow = -5,			//ʧ�ܣ����ݰ����
	ErrNetRlt_Failed_Handle_NULL = -6,       //ʧ�ܣ�����������
}EErrResultInfo;

//���ӷ������ɹ��ص���������
typedef void (*PFuncCliOnConnected)(HANDLE hHandle);

//�Ͽ����������ӻص���������
typedef void (*PFNCliOnTerminated)(HANDLE hHandle);

//������Ϣ�ص�����
typedef void (*PFNCliOnErrorInfo)(HANDLE hHandle, INT32 iModuleErr, INT32 iSysErr);

//֪ͨ��Ϣ�ص�����
typedef void (*PFNCliNotifyMsg)(HANDLE hHandle, CHAR* pchMsg);

//��ʼ����������
CLIAPI BOOL CLI_STDCALL CliInitEnv();


//������ģ�鿪�����������ӣ����ݵĽ��գ�����
//ע�⣬������Ҫ�����е�NewClient�����ľ�����е�ַ���ú�ſ��Ե���
//HTStart��HTStart֮�������ٴε���NewClient��HTSetSvrAddr
CLIAPI BOOL CLI_STDCALL CliStart();

//�½�һ�����ӣ�ÿ���ͻ��Ŷ�Ӧһ�����ӣ������n���ͻ���ͬʱ��¼����Ҫ
//����n��NewClient
CLIAPI HANDLE CLI_STDCALL CliNewClient();

//���÷�����IP��ַ����Ҫ��ÿ���ͻ�NewClient��������
CLIAPI void CLI_STDCALL CliSetSvrAddr(HANDLE hHandle, CHAR* pchBuf, UINT16 wPort);

//�������������ַ����Ҫ���ô˺��������������ͽ�������
CLIAPI void CLI_STDCALL CliClientJoin(HANDLE hHandle);

//��ֹ����
CLIAPI void CLI_STDCALL CliClose(HANDLE hHandle);

//ֹͣ����ģ��
CLIAPI void CLI_STDCALL CliStop();

//ж��
CLIAPI void CLI_STDCALL CliUninitEnv();

//�������ӷ������ص�����
CLIAPI void CLI_STDCALL CliSetConnectedFunc(PFuncCliOnConnected pfnConnected);

//���öϿ��������ص�����
CLIAPI void CLI_STDCALL CliSetTerminateFunc(PFNCliOnTerminated pfnOnTerminate);

//���ô�����Ϣ�ص�����
CLIAPI void CLI_STDCALL CliSetOnErrorInfoFunc(PFNCliOnErrorInfo pfnOnErrorInfo);

//������ʾ��Ϣ�ص�����
CLIAPI void CLI_STDCALL CliSetMsgCallBack(PFNCliNotifyMsg pfnNotifyMsg);

//////////////////////////////////////////////////////////////////////////
typedef void(*PFNCB_NotifyMsgNtf)(const char* pNtfMsg, UINT32 dwLen, HANDLE hHandle);

CLIAPI void CLI_STDCALL SetNotifyMsgNtf(PFNCB_NotifyMsgNtf pfnNotifyMsgNtf);

CLIAPI UINT16 CLI_STDCALL SendMsg(const char* pSendMsg, UINT32 dwSendMsgLen, HANDLE hHandle, UINT32* pdwSendID = NULL);


#ifdef __cplusplus
}
#endif

#endif