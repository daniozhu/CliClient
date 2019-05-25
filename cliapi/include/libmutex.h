#ifndef LIBMUTEX_H
#define LIBMUTEX_H

#include "libtype.h"
#include "libcondition.h"

#if !(defined(WIN32) || defined(WIN64))
#include <pthread.h>
#endif

#if (defined(WIN32) || defined(WIN64))
typedef CRITICAL_SECTION LibMutexId;
#else
typedef pthread_mutex_t LibMutexId;
#endif

BOOL LibMutexInit(LibMutexId & id);

void LibMutexLock(LibMutexId & id);

void LibMutexUnlock(LibMutexId & id);

BOOL LibMutexUninit(LibMutexId &id);


class CLibNonMutex
{
public:
    inline void  Lock() {}

    inline void  Unlock() {}

    inline void  LockRead() {}

    inline void  LockWrite() {}
};

class CLibMutex
{
    friend class CLibCondition;

public:
    CLibMutex();
    ~CLibMutex();

    void  Lock();

    void  Unlock();

    void  LockRead()
    {
        Lock();
    }

    void  LockWrite()
    {
        Lock();
    }

private:
    CLibMutex (const CLibMutex&);
    CLibMutex& operator= (const CLibMutex&);

private:
#if (defined(WIN32) || defined(WIN64))
    LibMutexId m_mutexId;
#else
    mutable LibMutexId m_mutexId;
#endif
};


class CLibRWMutex
{
public:
    CLibRWMutex();
    ~CLibRWMutex();

    void  LockRead();

    void  LockWrite();

    void  Lock();

    void  Unlock();

    unsigned int  ReaderCount() const;

    unsigned int  PendingWriterCount() const;

private:
    CLibMutex m_mutex;
    CLibCondition m_readCond;
    CLibCondition m_pendingWriteCond;
    unsigned int m_readerCount;
    bool m_hasWriterLock;
    unsigned int m_pendingWriteCount;
};


class CLibRecursiveMutex
{
public:
    CLibRecursiveMutex();
    ~CLibRecursiveMutex();

    void  Lock();

    void  Unlock();

    void  LockRead()
    {
        Lock();
    }

    void  LockWrite()
    {
        Lock();
    }
private:
    LibMutexId m_mutexId;
#if !(defined(WIN32) || defined(WIN64))
    pthread_mutexattr_t m_mutexAttr;
#endif
};

#endif

