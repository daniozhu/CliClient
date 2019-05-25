#ifndef LIBCRYPTODES_H
#define LIBCRYPTODES_H

#include "libdes.h"

//����key����
//pCtx     DES������
//acKey    8-byte ��Կ
void DESSetEncKey( LibDESContext *pCtx, UCHAR acKey[8] );

//����key����
//pCtx     DES������
//acKey    8-byte ��Կ
void DESSetDecKey( LibDESContext *pCtx, UCHAR acKey[8] );

void DESRandomKey( LibDESBlock *pKey );

//DES-ECB �ӽ���
//pCtx    DES ������
//acInput  64-bit �����
//acOutput 64-bit �����
//
void DESCryptECB( LibDESContext	*pCtx,
                 UCHAR acInput[8],
                 UCHAR acOutput[8] );

//DES-CBC buffer encryption/decryption
//pCtx        DES ������
//iMode       DES_ENCRYPT �� DES_DECRYPT
//iLength     �������ݵĳ���
//pIV         initialization vector (updated after use)
//pbyInput    ��������
//pbyOutput   �������
//
void DESCryptCBC( LibDESContext	*pCtx,
                 INT32			iMode,
                 INT32			iLength,
                 LibDESBlock	*pIV,
                 UCHAR			*pbyInput,
                 UCHAR			*pbyOutput);



//����һ�� 3-DES ��Կ
//pKey	3DES ��Կ
void GenDES3Key( LibDES3Block  *pKey );

//
//����һ�����ڼ��ܵ�3-DES��Կʱ���
//pCtx	�洢3-DES��Կʱ����������
//pKey  3-DES ��Կ
void DES3SetEncKey(LibDES3Context *pCtx, LibDES3Block *pKey);

//
//����һ�����ڽ��ܵ�3-DES��Կʱ���
//pCtx 	�洢3-DES��Կʱ����������
//pKey  3-DES ��Կ
void DES3SetDecKey( LibDES3Context *pCtx, LibDES3Block *pKey );


//3-DES ECB ����ģʽ
//pCtx	    3-DES ������
//byInput   ��������
//byOutput  ���
void DES3CryptECB( LibDES3Context *pCtx,
                  UCHAR byInput[8],
                  UCHAR byOutput[8] );

//
//3-DES CBC ����
//pCtx		3-DES ������
//iMode		�ӽ���ģʽ��DES_ENCRYPT����  DES_DECRYPT����
//iLength	���볤��
//pIv		3-DES��Կ
//pbyInput  ��������
//pacOutput �������
void DES3CryptCBC ( LibDES3Context *pCtx,
                   INT32		    iMode,
                   INT32		    iLength,
                   LibDES3Block*    pIV,
                   UCHAR*           pbyInput,
                   UCHAR*           pbyOutput );


//0 �ɹ�,  1 ʧ��
INT32 DESSelfTest( INT32 nVerbose );



#endif //LIB_CRYPTODES_H

