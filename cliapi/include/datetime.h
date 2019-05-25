#ifndef LIBTIME_H
#define LIBTIME_H

#include "libtype.h"

#include <ctime>
#include <string>

class CDateTime;

CDateTime TimeNow();

//日期时间类,代表1970年午夜到2037年之间的某一个时间
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

    // 设置本类所代表的日期时间
    // year [1970-2037]
    // month [1-12]
    // day [1-31]
    // hours  [0-23]
    // minutes [0-59]
    // seconds [0-59]
    BOOL SetDateTime(UINT32 year, UINT32 month, UINT32 day, UINT32 hours, UINT32 minutes, UINT32 seconds);

    // year [1970-2037]
    // month [1-12]
    // day 设定的此月的第几天[1-31]    
    BOOL SetDate(UINT32 year, UINT32 month, UINT32 day);

    // hours [0-23]
    // minutes 设定的此小时的第几分钟[0-59]
    // seconds 设定的此分钟的第几秒[0-59]
    BOOL SetTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    UINT32 GetYear() const;

    UINT32 GetMonth() const;

    UINT32 GetDay() const;

    UINT32 GetHour() const;

    UINT32 GetMinute() const;

    UINT32 GetSecond() const;

    UINT32 GetWeek() const;

    /**
    * @brief 将LibDateTime按某种格式进行格式化：YYYY-mm-dd hh:mm:ss
    * @param pszFormat : 时间格式
    * @return 格式化的字符串
    */
    std::string ToString(const TCHAR * pszFormat);

    /**
    * @brief 将LibDateTime按某种格式进行格式化(无参表示默认第一种格式)YYYY-mm-dd hh:mm:ss
    * @return 格式化的字符串
    */
    std::string ToString();

private:
    /**
    * @brief 不允许操作+
    */
    CDateTime & operator + (const CDateTime & datetime);

    /**
    * @brief 检查日期是否出处范围
    * @param year : 年份
    * @param month: 月份
    * @param day  : 日
    * @return TRUE:合法日期 FALSE:不合法日期
    */
    BOOL CheckDate(UINT32 year, UINT32 month, UINT32 day);

    /**
    * @brief 检查时间是否出处范围
    * @param hours   : 小时
    * @param minutes : 分钟
    * @param seconds : 秒
    * @return TRUE:合法时间 FALSE:不合法时间
    */
    BOOL CheckTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    tm m_time;
};



//是否为闰年
BOOL IsLeapYear(UINT32 year);

//启动到目前为止所经历的时间（有效时间为系统启动后49.7天内）
UINT64  LibGetTickCount();


void  LibSleep(UINT32 milliseconds);


//微妙时间
UINT64  TimeMicroSec();

//毫秒时间
UINT64  TimeMilliSec();

//秒时间
UINT64  TimeSecs();

//格式化
std::string TimeToString(const TCHAR* pszFormat, CDateTime t);

//格式化
std::string TimeToString(CDateTime t);


BOOL TimeFromString(std::string strDateTime,CDateTime& t);



#endif

