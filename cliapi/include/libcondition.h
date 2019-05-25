#ifndef LIBCONDITION_H
#define LIBCONDITION_H

//#ifndef WIN32
#if !(defined(WIN32) || defined(WIN64))
#  include <pthread.h>
#  include <errno.h>
#  include <sys/time.h>
#endif
#include "libtype.h"

#define CONDITION_WIN32_CONFORMANCE_TO_POSIX

    class CLibMutex;

    /**
    *@brief ���������������߳�ͬ��
    */
    class CLibCondition
    {
    public:

	/**
	* @brief ���캯������ʼ������
	*/
        CLibCondition();

	/**
	* @brief �����������ر��������
	*/
        ~CLibCondition();


        /**
        * @brief
        * �ȴ����������������������������һΪ�����ı䣬��Ϊ���жϣ���Ϊ��ʱ��
        * ��������������ԭ�ӵĽ��뻥�����Ļ��ⷶΧ�ڡ�
        * @param mutex : ������������صĻ�����������
        * @param dwMs : �ȴ���ʱʱ�䣬��λΪ����
        * @return TRUE ����������; FALSE ��ʱ���߱��ж�
        **/
        BOOL  Wait (CLibMutex &mutex, UINT32 dwMs = LIBINFINITE);



        /**
        * @brief
        * �ȴ����������������������������һΪ�����ı䣬��Ϊ���жϣ���Ϊ��ʱ.
        * ��������������ԭ�ӵĽ��뻥�����Ļ��ⷶΧ�ڡ�
        * @param mutex : ������������صĻ�������ָ��
        * @param dwMs : �ȴ���ʱʱ�䣬��λΪ����
        * @return TRUE ����������; FALSE ��ʱ���߱��ж�
        **/
        BOOL  Wait (CLibMutex *mutex, UINT32 dwMs = LIBINFINITE);

        /**
        * @brief
        * �������еȴ��е����һ���ȴ���Wait��
        * @return void
        **/
        void  Signal();

        /**
        * @brief
        * �������еĵȴ���Wait��
        * @return void
        **/
        void  Broadcast();

    private:

        //  no value sematics, therefore private and not implemented.
	/**
	* @brief �������캯��
	* @param CLibCondition���������
	*/
        CLibCondition (const CLibCondition&);

	/**
	* @brief ����=������,���ڶ���ĸ�ֵ
	* @param CLibCondition���������
	* @return CLibCondition���������
	*/
        CLibCondition& operator = (const CLibCondition&);

    private:
#if (defined(WIN32) || defined(WIN64))
#  ifdef CONDITION_WIN32_CONFORMANCE_TO_POSIX

        // boost clone with modification
        // licesnse text below

	/**
	* @brief �����¼����ź�״̬�ȴ���
	* @return void
	*/
        void EnterWait ();

        void* m_gate;
        void* m_queue;
        void* m_mutex;
        UINT32 m_gone;  // # threads that timed out and never made it to m_queue
        ULONG m_blocked; // # threads blocked on the condition
        UINT32 m_waiting; // # threads no longer waiting for the condition but
        // still waiting to be removed from m_queue
#  else
        HANDLE mId;
#  endif

#else
        mutable  pthread_cond_t mId;
#endif
    };


#endif


