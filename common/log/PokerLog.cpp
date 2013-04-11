
#include "PokerLog.h"

/**
 * ���캯��.
 * @author wangzhimin
 * @date 2009-12-06
 */
PokerLog::PokerLog()
    :m_bEnabled(true)
{
}

/**
 * ��������.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
PokerLog::~PokerLog()
{
}

/**
 * Ĭ�ϵĴ��ļ�����, ���Ե�ǰʱ��Ϊ�ļ���.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
bool PokerLog::Open()
{
    if (m_bEnabled)
    {
        //�õ����ڵ��ַ���
        string sDateStr = GetTimeStr("-", ".");

        return Open("Poker_" + sDateStr + ".Log");
    }

    return false;
}

/**
 * ��ָ�����ֵ��ļ�.
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
 * �ر��ļ�.
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
 * Log ʹ��.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
void PokerLog::Enable()
{
    m_bEnabled = true;
}

/**
 * Log ȥʹ��.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
void PokerLog::Disable()
{
    m_bEnabled = false;
}

/**
 * �õ���ǰʱ����ַ���
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
string PokerLog::GetTimeStr(string strDataDelim, string strTimeDelim)
{
    time_t tNowTime;
    time(&tNowTime);

    tm* tLocalTime = localtime(&tNowTime);

    //�õ�ʱ����ַ���
    string strTime = ValueToStr(tLocalTime->tm_year+1900, 4) + strDataDelim +
                     ValueToStr(tLocalTime->tm_mon+1, 2)     + strDataDelim +
                     ValueToStr(tLocalTime->tm_mday, 2)      + " " +
                     ValueToStr(tLocalTime->tm_hour, 2)      + strTimeDelim +
                     ValueToStr(tLocalTime->tm_min, 2)       + strTimeDelim +
                     ValueToStr(tLocalTime->tm_sec, 2);
    return strTime;
}

PokerLog pokerlog;

