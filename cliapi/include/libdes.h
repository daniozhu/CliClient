#ifndef LIBDES_H
#define LIBDES_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include "libtype.h"

#define DES_ENCRYPT  1
#define DES_DECRYPT  0

/**
* @brief typedef DES context structure
* key schedule table
* ����DES�����Ľṹ��
* �ؼ����ȱ�
*/
typedef struct tagDESContext
{
    INT32		nEnDecMode;			/**<encrypt/decrypt*/
    UINT32      aSubKey[32];		/**<DES sub-keys*/
} LibDESContext;

/**
* @brief typedef DES block structure
* 64bits key (equal to IV)
* ����DES��ṹ
* 64λkey������IV��
*/
typedef struct tagDESBlock
{
    UCHAR acBlock[8];
} LibDESBlock;

/**
* @brief typedef 3-DES context structure
* key schedule table
* ����3��DES�����Ľṹ��
* �ؼ����ȱ�
*/
typedef struct tagDES3Context
{
    INT32		nEnDecMode;			/**<encrypt/decrypt*/
    UINT32      aSubKey[96];		/**<DES sub-keys*/
} LibDES3Context;

/**
* @brief typedef 3-DES block structure
* 192bits key (equal to IV)
* ����3DES��ṹ��
* 192λkey������IV��
*/
typedef struct tagDES3Block
{
    UCHAR acBlock[24];
} LibDES3Block;


//�ӽ��ܷ�װ�֧࣬��3��DES��DES���ַ�ʽ
class CLibDes
{
public:
    /**
    * initialize des block ��ʼ��DES��
    * @param pIV : [in/out]DES block structure to be initialized
    * �������������������ʼ����DES��ṹ
    * @return void
    */
    void  DESGenKey(LibDESBlock *pIV);

    /**
    * initialize des-3 block ��ʼ��3��DES��
    * @param pIV : [in/out]DES-3 block structure to be initialized
    * �������������������ʼ����3��DES��ṹ
    * @return void
    */
    void  DESGenKey(LibDES3Block *pIV);

    /**
    * Generate DES encrypt key ����DES�����
    * @param pCtx : [in/out]DES context to be initialized
    * �������������������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void  DESGenEncKeySche(LibDESContext *pCtx, LibDESBlock &oKey);

    /**
    * Generate DES-3 encrypt key ����3��DES�����
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [�����������]������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void  DESGenEncKeySche(LibDES3Context *pCtx, LibDES3Block &oKey);

    /**
    * Generate DES decrypt key ����DES�����
    * @param pCtx : [in/out]DES context to be initialized
    * [�����������]������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void  DESGenDecKeySche(LibDESContext *pCtx, LibDESBlock &oKey);

    /**
    * Generate DES-3 decrypt key ����3��DES�����
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [�����������]������ʼ����3��DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void  DESGenDecKeySche(LibDES3Context *pCtx, LibDES3Block &oKey);

    /**
    * DES buffer encryption DES�������
    * @param pCtx : [in]DES context [�������]DES������
    * @param pIV :[in] DES block [�������]DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void  DESEncryptNCBC(LibDESContext *pCtx,
        LibDESBlock *pIV,
        INT32 nInLen,
        UCHAR *pInput,
        UCHAR *pOutput);

    /**
    * DES-3 buffer encryption 3��DES�������
    * @param pCtx : [in]DES-3 context [�������]3��DES������
    * @param pIV : [in]DES-3 block[�������] 3��DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void  DESEncryptNCBC(LibDES3Context *pCtx,
        LibDES3Block *pIV,
        INT32 nInLen,
        UCHAR *pInput,
        UCHAR *pOutput);

    /**
    * DES buffer decryption DES�������
    * @param pCtx : [in]DES context [�������]DES������
    * @param pIV : [in]DES block [�������]DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void  DESDecryptNCBC(LibDESContext *pCtx,
        LibDESBlock *pIV,
        INT32  nInLen,
        UCHAR *pInput,
        UCHAR *pOutput);

    /**
    * DES-3 buffer decryption 3��DES�������
    * @param pCtx : [in]DES-3 context [�������]3��DES������
    * @param pIV : [in]DES-3 block [�������]3��DES��
    * @param nInLen : [in]input buffer len [�������]���뻺�峤��
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void  DESDecryptNCBC(LibDES3Context *pCtx,
        LibDES3Block *pIV,
        INT32 nInLen,
        UCHAR *pInput,
        UCHAR *pOutput);



};

#endif //LIB_DES_H


