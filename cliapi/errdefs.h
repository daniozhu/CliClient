#ifndef ERRDEFS_INCLUDE_H
#define ERRDEFS_INCLUDE_H

enum errdefs
{
	ErrCode_Success                 = 0,
	ErrCode_Failed                  = 1,
	ErrCode_Failed_DB_NoData        = 2,
	ErrCode_Failed_DB_Exception     = 3,
	ErrCode_Failed_Unknown_Program_Prj  = 4,
	ErrCode_Failed_Unknown_Program_Module  = 5,
	ErrCode_Failed_Unknown_OpUser   = 6,
	ErrCode_Failed_Error_Password   = 7,
	ErrCode_Failed_Op_Not_Login     = 8,
	ErrCode_Failed_Delete_Prj_Not_Exist  = 9,
	ErrCode_Failed_Delete_Prj_DB_Error  = 9,
	ErrCode_Failed_Delete_Prj_Del_Module_Error  = 10,
	ErrCode_Failed_Delete_Module_Module_Not_Exist  = 11,
	ErrCode_Failed_Delete_Module_DB_Error  = 12,
	ErrCode_Failed_Update_Module_DB_Error  = 13,
	ErrCode_Failed_Update_Module_In_Updating  = 14,
	ErrCode_Failed_Update_Module_Unknown_Module_Data  = 15,
	ErrCode_Failed_Add_Module_In_Adding  = 16,
	ErrCode_Failed_Add_Module_Unknown_Module_Data  = 17,
	ErrCode_Failed_Module_Data_Error  = 18,
	ErrCode_Failed_Module_Data_ModuleID_Error  = 19,
	ErrCode_Failed_To_DB_Unknown_SessionID  = 20,
	ErrCode_Failed_To_DB_SaveModule_Error  = 21,
	ErrCode_Failed_To_DB_SaveModuleData_Error  = 22,
	ErrCode_Failed_To_DB_UpdateModule_Error  = 23,
	ErrCode_Failed_To_DB_UpdateModuleData_Error  = 24,
	ErrCode_Failed_To_DB_Data_Check_Error  = 25,
	ErrCode_Failed_Memory_Error     = 65534,
	ErrCode_Failed_Unknown_Error    = 65535,
};

extern const char* GetErrDesc(int iErrcode);
#endif
