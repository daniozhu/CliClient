#ifndef LIBLOCK_H
#define LIBLOCK_H

#include "libmutex.h"


template <class MT = CLibMutex>
class CLibLock
{
public:
    CLibLock(MT & mt):m_mutex(mt)
    {
        m_mutex.Lock();
    }
    ~CLibLock()
    {
        m_mutex.Unlock();
    }
private:
    MT & m_mutex;
};

typedef CLibLock<CLibMutex>  CLibMutexLock;

typedef CLibLock<CLibRecursiveMutex>  CLibRecursiveLock;

/**
*@brief �̶߳�ͬ��lock
*/
class CLibReadLock
{
public:
    CLibReadLock (CLibRWMutex &lock):m_mutex(lock)
    {
        m_mutex.LockRead();
    }
    ~CLibReadLock()
    {
        m_mutex.Unlock();
    }

private:
    CLibRWMutex & m_mutex;
};

/**
*@brief �߳�дͬ��lock
*/
class CLibWriteLock
{
public:
    CLibWriteLock (CLibRWMutex &lock):m_mutex(lock)
    {
        m_mutex.LockWrite();
    }
    ~CLibWriteLock()
    {
        m_mutex.Unlock();
    }

private:
    CLibRWMutex & m_mutex;
};



/**
* @brief �߳�ͬ��lock����Ҫ���ڴӽ���һ���������˳��ú������������̼�����
* ��ʹ�øо����ԣ��˼���Ϊ����Χ����һ�����뷶Χ��ֻ����һ���߳�ͬʱ���룩
* �ļ�������һ�������������󣨶���ĳ����(CriticalSection, Mutex��)�Ķ���ֻ����һ���߳�ռ�д���Դ��
* ������
* ����һ�����������ж���˳��㣬�Դ˺���ʹ�����ּ�������������������ԣ����ù��������´���ʱҪ������
* �������������д�����˳����룬�Ӷ��������
*/
template<class Mutex>
class CLibLockGuard
{
private:
    Mutex& m_lock;
public:
    CLibLockGuard(Mutex& oLock) : m_lock(oLock)
    {
        m_lock.Lock();
    }
    ~CLibLockGuard()
    {
        m_lock.Unlock();
    }

    class GuardOff
    {
        CLibLockGuard& m_guard;
    public:
        GuardOff(CLibLockGuard<Mutex>& g):m_guard(g)
        {
            m_guard.m_lock.Unlock();
        }
        ~GuardOff()
        {
            m_guard.m_lock.Lock();
        }
    };
};


#endif


