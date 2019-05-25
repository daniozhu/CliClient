#include "errdefs.h"

typedef struct tagCodeDescMap
{
    int iErrcode;
    const char* pszDesc;
}SCodeDescMap;

static const char* SDesc_ErrCode_Success                           = "�ɹ�";
static const char* SDesc_ErrCode_Failed                            = "ʧ��";
static const char* SDesc_ErrCode_Failed_DB_NoData                  = "ʧ�ܣ�û������";
static const char* SDesc_ErrCode_Failed_DB_Exception               = "ʧ�ܣ����ݿ��쳣";
static const char* SDesc_ErrCode_Failed_Unknown_Program_Prj        = "δ֪�ĳ�����Ŀ";
static const char* SDesc_ErrCode_Failed_Unknown_Program_Module     = "δ֪����ģ��";
static const char* SDesc_ErrCode_Failed_Unknown_OpUser             = "��Ч�û���";
static const char* SDesc_ErrCode_Failed_Error_Password             = "���벻��ȷ";
static const char* SDesc_ErrCode_Failed_Op_Not_Login               = "���ȵ�¼";
static const char* SDesc_ErrCode_Failed_Delete_Prj_Not_Exist       = "Ҫɾ������Ŀ������";
static const char* SDesc_ErrCode_Failed_Delete_Prj_DB_Error        = "ɾ����Ŀʧ�ܣ����ݿ����";
static const char* SDesc_ErrCode_Failed_Delete_Prj_Del_Module_Error  = "ɾ����Ŀʧ�ܣ�ɾ��ģ��ʧ��";
static const char* SDesc_ErrCode_Failed_Delete_Module_Module_Not_Exist  = "ɾ��ģ��ʧ�ܣ���Ч��ģ��";
static const char* SDesc_ErrCode_Failed_Delete_Module_DB_Error     = "ɾ��ģ��ʧ�ܣ����ݿ����";
static const char* SDesc_ErrCode_Failed_Update_Module_DB_Error     = "����ģ��ʧ�ܣ����ݿ����";
static const char* SDesc_ErrCode_Failed_Update_Module_In_Updating  = "����ģ��ʧ�ܣ���ģ�����ڸ���";
static const char* SDesc_ErrCode_Failed_Update_Module_Unknown_Module_Data  = "����ģ��ʧ�ܣ���������ģ����Ϣ";
static const char* SDesc_ErrCode_Failed_Add_Module_In_Adding       = "���ģ��ʧ�ܣ���ģ���������";
static const char* SDesc_ErrCode_Failed_Add_Module_Unknown_Module_Data  = "���ģ��ʧ�ܣ���������ģ����Ϣ";
static const char* SDesc_ErrCode_Failed_Module_Data_Error          = "ģ�����ݴ���";
static const char* SDesc_ErrCode_Failed_Module_Data_ModuleID_Error  = "����ģ������ʧ�ܣ�ģ��ID����";
static const char* SDesc_ErrCode_Failed_To_DB_Unknown_SessionID    = "��ǰ�û�����Ҫ���µ���Ϣ";
static const char* SDesc_ErrCode_Failed_To_DB_SaveModule_Error     = "дģ����Ϣ�����ݿ�ʧ��";
static const char* SDesc_ErrCode_Failed_To_DB_SaveModuleData_Error  = "дģ�����ݵ����ݿ�ʧ��";
static const char* SDesc_ErrCode_Failed_To_DB_UpdateModule_Error   = "����ģ����Ϣ�����ݿ�ʧ��";
static const char* SDesc_ErrCode_Failed_To_DB_UpdateModuleData_Error  = "����ģ�����ݵ����ݿ�ʧ��";
static const char* SDesc_ErrCode_Failed_To_DB_Data_Check_Error     = "��ӻ�������ݿ�ʧ�ܣ�����У�����";
static const char* SDesc_ErrCode_Failed_Memory_Error               = "�ڴ����";
static const char* SDesc_ErrCode_Failed_Unknown_Error              = "δ֪����";

SCodeDescMap gaMapArray[] = 
{
    {ErrCode_Success,  "�ɹ�"},
    {ErrCode_Failed,  "ʧ��"},
    {ErrCode_Failed_DB_NoData,  "ʧ�ܣ�û������"},
    {ErrCode_Failed_DB_Exception,  "ʧ�ܣ����ݿ��쳣"},
    {ErrCode_Failed_Unknown_Program_Prj,  "δ֪�ĳ�����Ŀ"},
    {ErrCode_Failed_Unknown_Program_Module,  "δ֪����ģ��"},
    {ErrCode_Failed_Unknown_OpUser,  "��Ч�û���"},
    {ErrCode_Failed_Error_Password,  "���벻��ȷ"},
    {ErrCode_Failed_Op_Not_Login,  "���ȵ�¼"},
    {ErrCode_Failed_Delete_Prj_Not_Exist,  "Ҫɾ������Ŀ������"},
    {ErrCode_Failed_Delete_Prj_DB_Error,  "ɾ����Ŀʧ�ܣ����ݿ����"},
    {ErrCode_Failed_Delete_Prj_Del_Module_Error,  "ɾ����Ŀʧ�ܣ�ɾ��ģ��ʧ��"},
    {ErrCode_Failed_Delete_Module_Module_Not_Exist,  "ɾ��ģ��ʧ�ܣ���Ч��ģ��"},
    {ErrCode_Failed_Delete_Module_DB_Error,  "ɾ��ģ��ʧ�ܣ����ݿ����"},
    {ErrCode_Failed_Update_Module_DB_Error,  "����ģ��ʧ�ܣ����ݿ����"},
    {ErrCode_Failed_Update_Module_In_Updating,  "����ģ��ʧ�ܣ���ģ�����ڸ���"},
    {ErrCode_Failed_Update_Module_Unknown_Module_Data,  "����ģ��ʧ�ܣ���������ģ����Ϣ"},
    {ErrCode_Failed_Add_Module_In_Adding,  "���ģ��ʧ�ܣ���ģ���������"},
    {ErrCode_Failed_Add_Module_Unknown_Module_Data,  "���ģ��ʧ�ܣ���������ģ����Ϣ"},
    {ErrCode_Failed_Module_Data_Error,  "ģ�����ݴ���"},
    {ErrCode_Failed_Module_Data_ModuleID_Error,  "����ģ������ʧ�ܣ�ģ��ID����"},
    {ErrCode_Failed_To_DB_Unknown_SessionID,  "��ǰ�û�����Ҫ���µ���Ϣ"},
    {ErrCode_Failed_To_DB_SaveModule_Error,  "дģ����Ϣ�����ݿ�ʧ��"},
    {ErrCode_Failed_To_DB_SaveModuleData_Error,  "дģ�����ݵ����ݿ�ʧ��"},
    {ErrCode_Failed_To_DB_UpdateModule_Error,  "����ģ����Ϣ�����ݿ�ʧ��"},
    {ErrCode_Failed_To_DB_UpdateModuleData_Error,  "����ģ�����ݵ����ݿ�ʧ��"},
    {ErrCode_Failed_To_DB_Data_Check_Error,  "��ӻ�������ݿ�ʧ�ܣ�����У�����"},
    {ErrCode_Failed_Memory_Error,  "�ڴ����"},
    {ErrCode_Failed_Unknown_Error,  "δ֪����"},
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
