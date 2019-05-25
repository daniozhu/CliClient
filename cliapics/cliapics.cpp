// 这是主 DLL 文件。

#include "stdafx.h"
#include "commonlib.h"
#include "cliapihelper.h"
#include "svrsessionmgr.h"
#include "cliapics.h"

namespace CliApiCS
{
    bool CliApi::Init(String^ ipAddr, UInt16 wPort)
    {
        CSvrSessionMgr::CreateInstance();

        char szIpAddr[256] = { 0 };

        CommonLib::LibNStrCpFromMStr(szIpAddr, sizeof(szIpAddr), ipAddr);

        if (!CSvrSessionMgr::Instance()->Init(szIpAddr, wPort))
        {
            return false;
        }

        return true;
    }

    bool CliApi::Start()
    {
        BOOL bSucc = CSvrSessionMgr::Instance()->Start();
        if (!bSucc)
        {
            return false;
        }

        return true;
    }

    void CliApi::Stop()
    {
        CSvrSessionMgr::Instance()->Uninit();
    }

    void CliApi::SetDlgtOnConnected(DlgtOnConnected^ dlgtOnConnected)
    {
        CliApi::s_dlgtOnConnected = dlgtOnConnected;
    }

    void CliApi::SetDlgtOnDisConnected(DlgtOnDisConnected^ dlgtOnDisConnected)
    {
        CliApi::s_dlgtOnDisConnected = dlgtOnDisConnected;
    }

    void CliApi::SetDlgtOnErrorInfo(DlgtOnErrorInfo^ dlgtOnErrorInfo)
    {
        CliApi::s_dlgtOnErrorInfo = dlgtOnErrorInfo;
    }

    void CliApi::SetDlgtOnMsgCallBack(DlgtOnMsgCallBack^ dlgtOnMsgCallBack)
    {
        CliApi::s_dlgtOnMsgCallBack = dlgtOnMsgCallBack;
    }

    void CliApi::SetDlgtOnNotifyMsgNtf(DlgtOnNotifyMsgNtf^ dlgtOnNotifyMsgNtf)
    {
        CliApi::s_dlgtOnNotifyMsgNtf = dlgtOnNotifyMsgNtf;
    }   

	UInt32 CliApi::SendMsg(String^ strMsg)
	{
		SvrSession^ svrSession = CSvrSessionMgr::Instance()->GetSvrSession();
		if (svrSession == nullptr)
		{
			return ErrNetRlt_Failed_Not_Connect;
		}

		return svrSession->SendToSvrMsg(strMsg);
	}
}