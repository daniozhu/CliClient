#include "errdefs.h"

typedef struct tagCodeDescMap
{
    int iErrcode;
    const char* pszDesc;
}SCodeDescMap;

static const char* SDesc_ErrCode_Success                           = "成功";
static const char* SDesc_ErrCode_Failed                            = "失败";
static const char* SDesc_ErrCode_Failed_DB_NoData                  = "失败，没有数据";
static const char* SDesc_ErrCode_Failed_DB_Exception               = "失败，数据库异常";
static const char* SDesc_ErrCode_Failed_Unknown_Program_Prj        = "未知的程序项目";
static const char* SDesc_ErrCode_Failed_Unknown_Program_Module     = "未知程序模块";
static const char* SDesc_ErrCode_Failed_Unknown_OpUser             = "无效用户名";
static const char* SDesc_ErrCode_Failed_Error_Password             = "密码不正确";
static const char* SDesc_ErrCode_Failed_Op_Not_Login               = "请先登录";
static const char* SDesc_ErrCode_Failed_Delete_Prj_Not_Exist       = "要删除的项目不存在";
static const char* SDesc_ErrCode_Failed_Delete_Prj_DB_Error        = "删除项目失败，数据库错误";
static const char* SDesc_ErrCode_Failed_Delete_Prj_Del_Module_Error  = "删除项目失败，删除模块失败";
static const char* SDesc_ErrCode_Failed_Delete_Module_Module_Not_Exist  = "删除模块失败，无效的模块";
static const char* SDesc_ErrCode_Failed_Delete_Module_DB_Error     = "删除模块失败，数据库错误";
static const char* SDesc_ErrCode_Failed_Update_Module_DB_Error     = "更新模块失败，数据库错误";
static const char* SDesc_ErrCode_Failed_Update_Module_In_Updating  = "更新模块失败，有模块正在更新";
static const char* SDesc_ErrCode_Failed_Update_Module_Unknown_Module_Data  = "更新模块失败，请先设置模块信息";
static const char* SDesc_ErrCode_Failed_Add_Module_In_Adding       = "添加模块失败，有模块正在添加";
static const char* SDesc_ErrCode_Failed_Add_Module_Unknown_Module_Data  = "添加模块失败，请先设置模块信息";
static const char* SDesc_ErrCode_Failed_Module_Data_Error          = "模块数据错误";
static const char* SDesc_ErrCode_Failed_Module_Data_ModuleID_Error  = "接收模块数据失败，模块ID错误";
static const char* SDesc_ErrCode_Failed_To_DB_Unknown_SessionID    = "当前用户无需要更新的信息";
static const char* SDesc_ErrCode_Failed_To_DB_SaveModule_Error     = "写模块信息到数据库失败";
static const char* SDesc_ErrCode_Failed_To_DB_SaveModuleData_Error  = "写模块数据到数据库失败";
static const char* SDesc_ErrCode_Failed_To_DB_UpdateModule_Error   = "更新模块信息到数据库失败";
static const char* SDesc_ErrCode_Failed_To_DB_UpdateModuleData_Error  = "更新模块数据到数据库失败";
static const char* SDesc_ErrCode_Failed_To_DB_Data_Check_Error     = "添加或更新数据库失败，数据校验错误";
static const char* SDesc_ErrCode_Failed_Memory_Error               = "内存错误";
static const char* SDesc_ErrCode_Failed_Unknown_Error              = "未知错误";

SCodeDescMap gaMapArray[] = 
{
    {ErrCode_Success,  "成功"},
    {ErrCode_Failed,  "失败"},
    {ErrCode_Failed_DB_NoData,  "失败，没有数据"},
    {ErrCode_Failed_DB_Exception,  "失败，数据库异常"},
    {ErrCode_Failed_Unknown_Program_Prj,  "未知的程序项目"},
    {ErrCode_Failed_Unknown_Program_Module,  "未知程序模块"},
    {ErrCode_Failed_Unknown_OpUser,  "无效用户名"},
    {ErrCode_Failed_Error_Password,  "密码不正确"},
    {ErrCode_Failed_Op_Not_Login,  "请先登录"},
    {ErrCode_Failed_Delete_Prj_Not_Exist,  "要删除的项目不存在"},
    {ErrCode_Failed_Delete_Prj_DB_Error,  "删除项目失败，数据库错误"},
    {ErrCode_Failed_Delete_Prj_Del_Module_Error,  "删除项目失败，删除模块失败"},
    {ErrCode_Failed_Delete_Module_Module_Not_Exist,  "删除模块失败，无效的模块"},
    {ErrCode_Failed_Delete_Module_DB_Error,  "删除模块失败，数据库错误"},
    {ErrCode_Failed_Update_Module_DB_Error,  "更新模块失败，数据库错误"},
    {ErrCode_Failed_Update_Module_In_Updating,  "更新模块失败，有模块正在更新"},
    {ErrCode_Failed_Update_Module_Unknown_Module_Data,  "更新模块失败，请先设置模块信息"},
    {ErrCode_Failed_Add_Module_In_Adding,  "添加模块失败，有模块正在添加"},
    {ErrCode_Failed_Add_Module_Unknown_Module_Data,  "添加模块失败，请先设置模块信息"},
    {ErrCode_Failed_Module_Data_Error,  "模块数据错误"},
    {ErrCode_Failed_Module_Data_ModuleID_Error,  "接收模块数据失败，模块ID错误"},
    {ErrCode_Failed_To_DB_Unknown_SessionID,  "当前用户无需要更新的信息"},
    {ErrCode_Failed_To_DB_SaveModule_Error,  "写模块信息到数据库失败"},
    {ErrCode_Failed_To_DB_SaveModuleData_Error,  "写模块数据到数据库失败"},
    {ErrCode_Failed_To_DB_UpdateModule_Error,  "更新模块信息到数据库失败"},
    {ErrCode_Failed_To_DB_UpdateModuleData_Error,  "更新模块数据到数据库失败"},
    {ErrCode_Failed_To_DB_Data_Check_Error,  "添加或更新数据库失败，数据校验错误"},
    {ErrCode_Failed_Memory_Error,  "内存错误"},
    {ErrCode_Failed_Unknown_Error,  "未知错误"},
};

const char* GetErrDesc(int iErrcode)
{
    int iSize = sizeof(gaMapArray)/sizeof(SCodeDescMap);

    for(int i = 0; i < iSize; i++)
    {
        if (gaMapArray[i].iErrcode == iErrcode)
        {
            return gaMapArray[i].pszDesc;
        }
    }
    return "Unknown Error";
}
