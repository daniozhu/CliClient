#ifndef LIBSTRING_H
#define LIBSTRING_H

#include "libtype.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <vector>
#include <stdarg.h>

#if (defined(WIN32) || defined(WIN64))
#include <tchar.h>
#define LIBSYMBOL_RT         "\r\n"
#define LIBFMT_I64           "%I64d"
#define LIBFMT_U64           "%I64u"
#define LIBFMT_X64           "%I64x"
#else
#include <wchar.h>
#include <wctype.h>
#define LIBSYMBOL_RT         "\n"
#define LIBFMT_I64           "%lld"
#define LIBFMT_U64           "%llu"
#define LIBFMT_64X           "%llx"
#endif

#define LibIsAlNum(c) (isalnum(((UCHAR)(c))))

#define LibIsAlpha(c) (isalpha(((UCHAR)(c))))

#define LibIsCntrl(c) (iscntrl(((UCHAR)(c))))

#define LibIsDigit(c) (isdigit(((UCHAR)(c))))

#define LibISGraph(c) (isgraph(((UCHAR)(c))))

#define LibIsLower(c) (islower(((UCHAR)(c))))

#ifdef isascii
#define LibIsAscii(c) (isascii(((UCHAR)(c))))
#else
#define LibIsAscii(c) (((c) & ~0x7f)==0)
#endif

#define LibIsPrint(c) (isprint(((UCHAR)(c))))

#define LibIsPunct(c) (ispunct(((UCHAR)(c))))

#define LibIsSpace(c) (isspace(((UCHAR)(c))))

#define LibIsUpper(c) (isupper(((UCHAR)(c))))

#define LibIsXdigit(c) (isxdigit(((UCHAR)(c))))

#define LibToLower(c) (tolower(((UCHAR)(c))))

#define LibToUpper(c) (toupper(((UCHAR)(c))))

///////////////////////////////////////////////////////////////////////////
#define LibSprintf sprintf

#if (defined(WIN32) || defined(WIN64))
#define LibSnprintf _snprintf
#else
#define LibSnprintf snprintf
#endif

///////////////////////////////////////////////////////////////////////
#define LibAtoi atoi

#if (defined(WIN32) || defined(WIN64))
#define LibAtoi64 _atoi64
#else
#define LibAtoi64 atoll
#endif


#define _LibTStrlen            LibStrlen
#define _LibTStrnlen           LibStrnlen
#define _LibTStrcat            LibStrcat
#define _LibTStrcpy            LibStrcpy
#define _LibTStrncpy           LibStrncpy
#define _LibTStrcmp            LibStrcmp
#define _LibTStrncmp           LibStrncmp
#define _LibTStrchr            LibStrchr
#define _LibTStrrchr           LibStrrchr
#define _LibTStrcasecmp        LibStrcasecmp
#define _LibTTtoi		       LibAtoi
#ifdef __linux__
#define _LibTsnprintf		   snprintf
#else
#define _LibTsnprintf		   _snprintf
#endif
#define _LibTvsprintf          vsprintf
#define _LibTvsnprintf         vsnprintf
#define _LibTsprintf		   sprintf
#define _LibTStrchr            LibStrchr
#define _LibTStrrchr           LibStrrchr
#define _LibTStrtok            LibStrtok
#define _LibTStrlwr            LibStrlwr
#define _LibTStrupr            LibStrupr
#define _LibTStrcat            LibStrcat
#define _LibTStrncat           LibStrncat
#define _LibTStrncasecmp       LibStrncasecmp
#define _LibTBufferToHex       LibBufferToHexA
#define _LibTIntToHex          LibIntToHexA
#define _LibTStrTrimLeft       LibStrTrimLeftA
#define _LibTStrTrimRight      LibStrTrimRightA
#define _LibTStrTrim           LibStrTrimA
#define _LibTStrtod            LibStrtod
#define _LibTSplitStrings      LibSplitStringsA
#define _LibTAtou64            LibAtou64
#define _LibTAtou              LibAtou
#define _LibTItoa              LibItow
#define _LibTItoa64            LibItow64
#define _LibTUtoa              LibUtow
#define _LibTUtoa64            LibUtow64


inline UINT32  LibStrlen( const CHAR* string )
{
    return (UINT32)strlen(string);
}

inline UINT32  LibStrnlen(const CHAR* pszStr, UINT32 sizeInBytes )
{
    return (UINT32)strnlen(pszStr, sizeInBytes);
}

inline CHAR*  LibStrcat(CHAR* strDestination, const CHAR* strSource )
{
    return strcat(strDestination, strSource);
}

inline CHAR *  LibStrSafeCat(CHAR* strDestination, UINT32 dstLen, const CHAR* strSource)
{
    if (dstLen < strlen(strDestination) + strlen(strSource) + 1)
    {
        return NULL;
    }
    return strcat(strDestination,strSource);
}

inline CHAR*  LibStrncat(CHAR *strDestination, const CHAR *strSource, UINT32 len)
{
    return strncat(strDestination, strSource, len);
}


inline CHAR*  LibStrcpy( CHAR *strDestination, const CHAR *strSource )
{
    return strcpy(strDestination, strSource);
}

inline CHAR* LibStrSafeCpy( char *strDestination, size_t numberOfElements, const CHAR *strSource )
{
    if (numberOfElements  < strlen(strSource) +1)
    {
        return NULL;
    }

    return strncpy(strDestination,strSource,numberOfElements);
}

template <class T>
inline void LibStrSafeCpy(T& Destination, const char* Source) 
{
    (static_cast<char[sizeof(Destination)]>(Destination));

    LibStrSafeCpy(Destination, Source, sizeof(Destination));
}

inline WCHAR*  LibWcscpy( WCHAR *strDestination, const WCHAR *strSource )
{
    return wcscpy(strDestination, strSource);
}

WCHAR * LibWcsSafeCpy( WCHAR *strDestination, size_t numberOfElements, const WCHAR *strSource );

inline CHAR*  LibStrncpy( CHAR *strDestination, const CHAR *strSource, UINT32 len )
{
    return strncpy(strDestination, strSource, len);
}

inline WCHAR*  LibWcsncpy( WCHAR *strDestination, const WCHAR *strSource, UINT32 len )
{
    return wcsncpy(strDestination, strSource, len);
}

inline INT32  LibStrcmp( const CHAR *string1, const CHAR *string2 )
{
    return strcmp(string1, string2);
}

inline INT32  LibWcscmp( const WCHAR *string1, const WCHAR *string2 )
{
    return wcscmp(string1, string2);
}

inline INT32  LibStrncmp( const CHAR *string1, const CHAR *string2, UINT32 count )
{
    return strncmp( string1, string2, count );
}

inline INT32  LibWcsncmp( const WCHAR *string1, const WCHAR *string2, size_t count )
{
    return wcsncmp( string1, string2, count );
}

inline CHAR*  LibStrchr( const CHAR *string, INT32 c )
{
    return (CHAR*)strchr(string, c);
}

inline WCHAR*  LibWcschr( const WCHAR *string, WCHAR c )
{
    return (WCHAR*)wcschr(string, c);
}

inline CHAR*  LibStrrchr( const CHAR *string, INT32 c )
{
    return (CHAR*)strrchr(string ,c);
}

wchar_t*  LibWcsrchr( const wchar_t *string, wchar_t c );

inline INT32  LibStrcasecmp(const CHAR *s1, const CHAR *s2)
{
#if (defined(WIN32) || defined(WIN64))
    return _stricmp(s1, s2);
#else
    return strcasecmp(s1, s2);
#endif
}

inline INT32  LibStrncasecmp(const CHAR *s1, const CHAR *s2, UINT32 count)
{
#if (defined(WIN32) || defined(WIN64))
    return _strnicmp(s1, s2, count);
#else
    return strncasecmp(s1, s2, count);
#endif
}

INT32  LibWcscasecmp(const wchar_t *s1, const wchar_t *s2);

INT32  LibWcsncasecmp(const wchar_t *s1, const wchar_t *s2, UINT32 count);

inline CHAR*  LibStrtok(CHAR *pszStr, const CHAR *delim)
{
    return strtok(pszStr, delim);
}

inline wchar_t*  LibWcstok(wchar_t *pszStr, const wchar_t *delim);

CHAR*  LibStrlwr(CHAR* pszStr);

CHAR*  LibStrupr(CHAR* pszStr);


UINT32  LibAtou(const CHAR* pStr);

UINT64  LibAtou64(const CHAR* pStr); 

inline INT32  LibItoa(CHAR* pBuf, UINT32 buflen, INT32 dwNum)
{
    return LibSnprintf(pBuf, buflen, "%d", dwNum);
}

inline INT32  LibItoa64(CHAR *pBuf, UINT32 buflen, INT64 dqNum)
{
    return LibSnprintf(pBuf, buflen, LIBFMT_I64 , dqNum);
}

inline INT32  LibUtoa(CHAR *pBuf, UINT32 buflen, UINT32 dwNum)
{
    return LibSnprintf(pBuf, buflen, "%u", dwNum);
}


inline INT32  LibUtoa64(CHAR* pBuf,UINT32 buflen, UINT64 dqNum)
{
    return LibSnprintf(pBuf, buflen, LIBFMT_U64, dqNum);
}

inline DOUBLE  LibStrtod(const CHAR *nptr, CHAR **endptr)
{
    return strtod(nptr, endptr);
}

std::vector<std::string>  LibSplitStringsA(const std::string &sSource, CHAR delim);

std::string  LibStrupr(std::string &pszStr);

std::string  LibStrlwr(std::string &pszStr);

template <class T>
inline void  LibZeroString(T &Destination) throw()
{
    (static_cast<CHAR[sizeof(Destination)]>(Destination));
    Destination[0] = '\0';
    Destination[sizeof(Destination)-1] = '\0';
}

std::string  LibBufferToHexA(const CHAR *pBuf, UINT32 bufLen, const CHAR *pSplitter = "", INT32 lineLen = -1);

std::string  LibIntToHexA(INT32 dwNum);

std::string  LibStrTrimLeftA(std::string &pszStr, const CHAR *pTrimStr = " \r\t\n");

std::string  LibStrTrimRightA(std::string &pszStr, const CHAR *pTrimStr = " \r\t\n");

std::string  LibStrTrimA(std::string &pszStr, const CHAR* pTrimStr = " \r\t\n");

template <class T>
inline void LibSafeSprintf(T& Destination, const CHAR *format, ...)
{
    (static_cast<char[sizeof(Destination)]>(Destination));

    va_list args;
    va_start(args,format);
    _vsnprintf(Destination, sizeof(Destination)-1, format, args);
    va_end(args);
    Destination[sizeof(Destination)-1] = '\0';
}

#endif


