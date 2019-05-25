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
	ErrNetRlt_Succ = 0,						//发送成功
	ErrNetRlt_Failed_Not_Connect = -1,		//失败，没有连接服务器
	ErrNetRlt_Failed_Encode = -2,			//失败，组包错误
	ErrNetRlt_Failed_Zip = -3,				//失败，压缩失败
	ErrNetRlt_Failed_Conn_Err = -4,			//失败，socket连接错误
	ErrNetRlt_Failed_Overflow = -5,			//失败，数据包溢出
	ErrNetRlt_Failed_Handle_NULL = -6,       //失败，传入句柄错误
}EErrResultInfo;

//连接服务器成功回调函数定义
typedef void (*PFuncCliOnConnected)(HANDLE hHandle);

//断开服务器连接回调函数定义
typedef void (*PFNCliOnTerminated)(HANDLE hHandle);

//错误信息回调函数
typedef void (*PFNCliOnErrorInfo)(HANDLE hHandle, INT32 iModuleErr, INT32 iSysErr);

//通知信息回调函数
typedef void (*PFNCliNotifyMsg)(HANDLE hHandle, CHAR* pchMsg);

//初始化环境变量
CLIAPI BOOL CLI_STDCALL CliInitEnv();


//将网络模块开启，进行连接，数据的接收，发送
//注意，这里需要对所有的NewClient参数的句柄进行地址设置后才可以调用
//HTStart，HTStart之后不容许再次调用NewClient和HTSetSvrAddr
CLIAPI BOOL CLI_STDCALL CliStart();

//新建一个连接，每个客户号对应一个连接，如果有n个客户号同时登录，需要
//调用n次NewClient
CLIAPI HANDLE CLI_STDCALL CliNewClient();

//设置服务器IP地址，需要对每个客户NewClient进行设置
CLIAPI void CLI_STDCALL CliSetSvrAddr(HANDLE hHandle, CHAR* pchBuf, UINT16 wPort);

//设置完服务器地址后，需要调用此函数才能正常发送接收数据
CLIAPI void CLI_STDCALL CliClientJoin(HANDLE hHandle);

//终止链接
CLIAPI void CLI_STDCALL CliClose(HANDLE hHandle);

//停止网络模块
CLIAPI void CLI_STDCALL CliStop();

//卸载
CLIAPI void CLI_STDCALL CliUninitEnv();

//设置连接服务器回调函数
CLIAPI void CLI_STDCALL CliSetConnectedFunc(PFuncCliOnConnected pfnConnected);

//设置断开服务器回调函数
CLIAPI void CLI_STDCALL CliSetTerminateFunc(PFNCliOnTerminated pfnOnTerminate);

//设置错误信息回调函数
CLIAPI void CLI_STDCALL CliSetOnErrorInfoFunc(PFNCliOnErrorInfo pfnOnErrorInfo);

//设置提示信息回调函数
CLIAPI void CLI_STDCALL CliSetMsgCallBack(PFNCliNotifyMsg pfnNotifyMsg);

//////////////////////////////////////////////////////////////////////////
typedef void(*PFNCB_NotifyMsgNtf)(const char* pNtfMsg, UINT32 dwLen, HANDLE hHandle);

CLIAPI void CLI_STDCALL SetNotifyMsgNtf(PFNCB_NotifyMsgNtf pfnNotifyMsgNtf);

CLIAPI UINT16 CLI_STDCALL SendMsg(const char* pSendMsg, UINT32 dwSendMsgLen, HANDLE hHandle, UINT32* pdwSendID = NULL);


#ifdef __cplusplus
}
#endif

#endif