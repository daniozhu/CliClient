#ifndef LIBTYPE_H
#define LIBTYPE_H

#include <string>
#include <wchar.h>
#ifdef _M_X64
#ifndef WIN64
#define WIN64
#endif
#endif

#if defined(__linux__)
#define LINUX32
#if defined(__x86_64__)
#undef  LINUX32
#define LINUX64
#endif
#endif

#if (defined(WIN32) || defined(WIN64))
#pragma warning(disable:4996) 
#pragma warning(disable:4786)
#include <WinSock2.h>
#include <Windows.h>
#include <BaseTsd.h>
#include <tchar.h>


#define LIBAPI __stdcall      

typedef HANDLE               LIBHANDLE;
#define LIBINVALID_HANDLE    NULL
#define LibCloseHandle(x)    CloseHandle(x)

#else

typedef  unsigned char      BYTE;

#ifndef FALSE
#define FALSE			    false
#endif

#ifndef TRUE
#define TRUE                true
#endif

typedef wchar_t             WCHAR;

typedef char                CHAR;

typedef unsigned char       UCHAR;

typedef signed char         INT8;

typedef unsigned char       UINT8;

typedef signed short        INT16;

typedef unsigned short      UINT16;

typedef signed int          INT32;

typedef unsigned int        UINT32;

typedef  INT32              BOOL;

typedef long				LONG;
typedef unsigned long       ULONG;		

typedef signed long long    INT64;

typedef unsigned long long  UINT64;

typedef float               FLOAT;

#define LIBINVALID_HANDLE    0
typedef long                LIBHANDLE;

#define LibCloseHandle(x)    (x)

#ifdef UNICODE
typedef WCHAR               TCHAR;
#else
typedef CHAR                TCHAR;
#endif
#define LIBAPI 
#endif //endif __linux__


#define LIB_OK     0
#define LIB_ERR    0xFFFFFFFF

#define LIBINFINITE  0xFFFFFFFF
#ifndef NULL
typedef 0                   NULL 
#endif

typedef double              DOUBLE;

#endif





