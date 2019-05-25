// CliApiCS.h

#pragma once

#include "svrsession.h"

using namespace System;

namespace CliApiCS {
	
	public delegate Void DlgtOnConnected();

	public delegate Void DlgtOnDisConnected();

	public delegate Void DlgtOnErrorInfo(Int32 iModuleErr, Int32 iSysErr);

	public delegate Void DlgtOnMsgCallBack(String^ strMsg);

    public delegate void DlgtOnNotifyMsgNtf(String^ strNtfMsg);

	public ref class CliApi
	{
	public:
		//初始化
		static bool Init(String^ ipAddr, UInt16 wPort);

		//启动
		static bool Start();

		//停止
		static void Stop();

		//连接回调函数设置
		static void SetDlgtOnConnected(DlgtOnConnected^ dlgtOnConnected);

		//断开回调函数设置
		static void SetDlgtOnDisConnected(DlgtOnDisConnected^ dlgtOnDisConnected);

		//设置错误信息回调函数
		static void SetDlgtOnErrorInfo(DlgtOnErrorInfo^ dlgtOnErrorInfo);

		//设置消息提示回调函数
		static void SetDlgtOnMsgCallBack(DlgtOnMsgCallBack^ dlgtOnMsgCallBack);

        static void SetDlgtOnNotifyMsgNtf(DlgtOnNotifyMsgNtf^ dlgtOnNotifyMsgNtf);

		static UInt32 SendMsg(String^ strMsg);

	internal:
		static DlgtOnConnected^ s_dlgtOnConnected = nullptr;

		static DlgtOnDisConnected^ s_dlgtOnDisConnected = nullptr;

		static DlgtOnErrorInfo^ s_dlgtOnErrorInfo = nullptr;

		static DlgtOnMsgCallBack^ s_dlgtOnMsgCallBack = nullptr;

        static DlgtOnNotifyMsgNtf^ s_dlgtOnNotifyMsgNtf = nullptr;
	};
}
