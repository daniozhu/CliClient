#ifndef LIBTIME_H
#define LIBTIME_H

#include "libtype.h"

#include <ctime>
#include <string>

class CDateTime;

CDateTime TimeNow();

//����ʱ����,����1970����ҹ��2037��֮���ĳһ��ʱ��
class  CDateTime
{
public:
    CDateTime(time_t t = 0);

    time_t GetTimeValue();

    void SetTimeValue(time_t t);

    INT64 operator - (const CDateTime &datetime);

    INT64 DiffSecond(const CDateTime &datetime);

    INT64 DiffMinute(const CDateTime &datetime);

    INT64 DiffHour(const CDateTime &datetime);

    INT64 DiffDay(const CDateTime &datetime);

    INT64 DiffWeek(const CDateTime &datetime);

    INT32 DiffMonth(const CDateTime &datetime);

    INT32 DiffYear(const CDateTime &datetime);

    CDateTime & IncYear(UINT32 year = 1);

    CDateTime & DecYear(UINT32 year = 1);

    CDateTime & IncMonth(UINT32 month = 1);

    CDateTime & DecMonth(UINT32 month = 1);

    CDateTime & IncDay(UINT32 day = 1);

    CDateTime & DecDay(UINT32 day = 1);

    CDateTime & IncHour(UINT32 hour = 1);

    CDateTime & DecHour(UINT32 hour = 1);

    CDateTime & IncMinute(UINT32 minute = 1);

    CDateTime & DecMinute(UINT32 minute = 1);

    CDateTime & IncSecond(UINT32 second = 1);

    CDateTime & DecSecond(UINT32 second = 1);

    CDateTime & IncWeek(UINT32 week = 1);

    CDateTime & DecWeek(UINT32 week = 1);

    // ���ñ��������������ʱ��
    // year [1970-2037]
    // month [1-12]
    // day [1-31]
    // hours  [0-23]
    // minutes [0-59]
    // seconds [0-59]
    BOOL SetDateTime(UINT32 year, UINT32 month, UINT32 day, UINT32 hours, UINT32 minutes, UINT32 seconds);

    // year [1970-2037]
    // month [1-12]
    // day �趨�Ĵ��µĵڼ���[1-31]    
    BOOL SetDate(UINT32 year, UINT32 month, UINT32 day);

    // hours [0-23]
    // minutes �趨�Ĵ�Сʱ�ĵڼ�����[0-59]
    // seconds �趨�Ĵ˷��ӵĵڼ���[0-59]
    BOOL SetTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    UINT32 GetYear() const;

    UINT32 GetMonth() const;

    UINT32 GetDay() const;

    UINT32 GetHour() const;

    UINT32 GetMinute() const;

    UINT32 GetSecond() const;

    UINT32 GetWeek() const;

    /**
    * @brief ��LibDateTime��ĳ�ָ�ʽ���и�ʽ����YYYY-mm-dd hh:mm:ss
    * @param pszFormat : ʱ���ʽ
    * @return ��ʽ�����ַ���
    */
    std::string ToString(const TCHAR * pszFormat);

    /**
    * @brief ��LibDateTime��ĳ�ָ�ʽ���и�ʽ��(�޲α�ʾĬ�ϵ�һ�ָ�ʽ)YYYY-mm-dd hh:mm:ss
    * @return ��ʽ�����ַ���
    */
    std::string ToString();

private:
    /**
    * @brief ���������+
    */
    CDateTime & operator + (const CDateTime & datetime);

    /**
    * @brief ��������Ƿ������Χ
    * @param year : ���
    * @param month: �·�
    * @param day  : ��
    * @return TRUE:�Ϸ����� FALSE:���Ϸ�����
    */
    BOOL CheckDate(UINT32 year, UINT32 month, UINT32 day);

    /**
    * @brief ���ʱ���Ƿ������Χ
    * @param hours   : Сʱ
    * @param minutes : ����
    * @param seconds : ��
    * @return TRUE:�Ϸ�ʱ�� FALSE:���Ϸ�ʱ��
    */
    BOOL CheckTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    tm m_time;
};



//�Ƿ�Ϊ����
BOOL IsLeapYear(UINT32 year);

//������ĿǰΪֹ��������ʱ�䣨��Чʱ��Ϊϵͳ������49.7���ڣ�
UINT64  LibGetTickCount();


void  LibSleep(UINT32 milliseconds);


//΢��ʱ��
UINT64  TimeMicroSec();

//����ʱ��
UINT64  TimeMilliSec();

//��ʱ��
UINT64  TimeSecs();

//��ʽ��
std::string TimeToString(const TCHAR* pszFormat, CDateTime t);

//��ʽ��
std::string TimeToString(CDateTime t);


BOOL TimeFromString(std::string strDateTime,CDateTime& t);



#endif

