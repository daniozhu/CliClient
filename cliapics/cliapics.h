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
		//��ʼ��
		static bool Init(String^ ipAddr, UInt16 wPort);

		//����
		static bool Start();

		//ֹͣ
		static void Stop();

		//���ӻص���������
		static void SetDlgtOnConnected(DlgtOnConnected^ dlgtOnConnected);

		//�Ͽ��ص���������
		static void SetDlgtOnDisConnected(DlgtOnDisConnected^ dlgtOnDisConnected);

		//���ô�����Ϣ�ص�����
		static void SetDlgtOnErrorInfo(DlgtOnErrorInfo^ dlgtOnErrorInfo);

		//������Ϣ��ʾ�ص�����
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
