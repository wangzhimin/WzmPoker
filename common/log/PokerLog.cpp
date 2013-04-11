
#include "PokerLog.h"

/**
 * 构造函数.
 * @author wangzhimin
 * @date 2009-12-06
 */
PokerLog::PokerLog()
    :m_bEnabled(true)
{
}

/**
 * 析构函数.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
PokerLog::~PokerLog()
{
}

/**
 * 默认的打开文件操作, 会以当前时间为文件名.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
bool PokerLog::Open()
{
    if (m_bEnabled)
    {
        //得到日期的字符串
        string sDateStr = GetTimeStr("-", ".");

        return Open("Poker_" + sDateStr + ".Log");
    }

    return false;
}

/**
 * 打开指定名字的文件.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
bool PokerLog::Open(string sFileName)
{
    m_tOLogFile.open(sFileName.c_str(), ios_base::out | ios_base::app);

    if( !m_tOLogFile )
    {
        return false;
    }

    return true;
}

/**
 * 关闭文件.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
void PokerLog::Close()
{
    if (m_bEnabled)
    {
        if(m_tOLogFile.is_open())
        {
            m_tOLogFile.close();
        }
    }
}

/**
 * Log 使能.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
void PokerLog::Enable()
{
    m_bEnabled = true;
}

/**
 * Log 去使能.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
void PokerLog::Disable()
{
    m_bEnabled = false;
}

/**
 * 得到当前时间的字符串
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
string PokerLog::GetTimeStr(string strDataDelim, string strTimeDelim)
{
    time_t tNowTime;
    time(&tNowTime);

    tm* tLocalTime = localtime(&tNowTime);

    //得到时间的字符串
    string strTime = ValueToStr(tLocalTime->tm_year+1900, 4) + strDataDelim +
                     ValueToStr(tLocalTime->tm_mon+1, 2)     + strDataDelim +
                     ValueToStr(tLocalTime->tm_mday, 2)      + " " +
                     ValueToStr(tLocalTime->tm_hour, 2)      + strTimeDelim +
                     ValueToStr(tLocalTime->tm_min, 2)       + strTimeDelim +
                     ValueToStr(tLocalTime->tm_sec, 2);
    return strTime;
}

PokerLog pokerlog;

