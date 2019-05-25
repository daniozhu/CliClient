#ifndef LIBCRYPTODES_H
#define LIBCRYPTODES_H

#include "libdes.h"

//加密key设置
//pCtx     DES上下文
//acKey    8-byte 密钥
void DESSetEncKey( LibDESContext *pCtx, UCHAR acKey[8] );

//解密key设置
//pCtx     DES上下文
//acKey    8-byte 密钥
void DESSetDecKey( LibDESContext *pCtx, UCHAR acKey[8] );

void DESRandomKey( LibDESBlock *pKey );

//DES-ECB 加解密
//pCtx    DES 上下文
//acInput  64-bit 输入块
//acOutput 64-bit 输出块
//
void DESCryptECB( LibDESContext	*pCtx,
                 UCHAR acInput[8],
                 UCHAR acOutput[8] );

//DES-CBC buffer encryption/decryption
//pCtx        DES 上下文
//iMode       DES_ENCRYPT 或 DES_DECRYPT
//iLength     输入数据的长度
//pIV         initialization vector (updated after use)
//pbyInput    输入数据
//pbyOutput   输出数据
//
void DESCryptCBC( LibDESContext	*pCtx,
                 INT32			iMode,
                 INT32			iLength,
                 LibDESBlock	*pIV,
                 UCHAR			*pbyInput,
                 UCHAR			*pbyOutput);



//产生一个 3-DES 密钥
//pKey	3DES 密钥
void GenDES3Key( LibDES3Block  *pKey );

//
//产生一个用于加密的3-DES密钥时间表
//pCtx	存储3-DES密钥时间表的上下文
//pKey  3-DES 密钥
void DES3SetEncKey(LibDES3Context *pCtx, LibDES3Block *pKey);

//
//产生一个用于解密的3-DES密钥时间表
//pCtx 	存储3-DES密钥时间表的上下文
//pKey  3-DES 密钥
void DES3SetDecKey( LibDES3Context *pCtx, LibDES3Block *pKey );


//3-DES ECB 加密模式
//pCtx	    3-DES 上下文
//byInput   输入数据
//byOutput  输出
void DES3CryptECB( LibDES3Context *pCtx,
                  UCHAR byInput[8],
                  UCHAR byOutput[8] );

//
//3-DES CBC 加密
//pCtx		3-DES 上下文
//iMode		加解密模式：DES_ENCRYPT加密  DES_DECRYPT解密
//iLength	输入长度
//pIv		3-DES密钥
//pbyInput  输入数据
//pacOutput 输出数据
void DES3CryptCBC ( LibDES3Context *pCtx,
                   INT32		    iMode,
                   INT32		    iLength,
                   LibDES3Block*    pIV,
                   UCHAR*           pbyInput,
                   UCHAR*           pbyOutput );


//0 成功,  1 失败
INT32 DESSelfTest( INT32 nVerbose );



#endif //LIB_CRYPTODES_H

