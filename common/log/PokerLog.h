
#ifndef Poker_LOG_H
#define Poker_LOG_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

/**
 * 用于输出log文件的类.
 *
 * @author wangzhimin
 * @date 2009-12-06
 */
class PokerLog
{
public:
    PokerLog();
    ~PokerLog();

    bool Open();
    bool Open(string sFileName);
    void Close();

    void Enable();
    void Disable();

    /**
     * 输出操作符 <<.
     *
     * @author wangzhimin
     * @date 2009-12-06
     */
    template <typename T> PokerLog& operator<<(const T& value)
    {
        if (m_bEnabled)
        {
            m_tOLogFile << value;
            cout << value;
        }
        return (*this);
    }

    /**
     * 输出函数指针, 比如endl.
     *
     * @author wangzhimin
     * @date 2009-12-06
     */
    PokerLog& operator<<(ostream& (*_Pfn)(ostream&))
    {
        if (m_bEnabled)
        {
            (*_Pfn)(m_tOLogFile);
            (*_Pfn)(cout);
        }
        return (*this);
    }

    string GetTimeStr(string strDataDelim, string strTimeDelim);

private:
    /**
     * 数值转换为字符串.
     *
     * @author wangzhimin
     * @date 2009-12-06
     */
    template<typename T> string ValueToStr(T value, int format)
    {
        ostringstream ost;
        ost << setw(format) << setfill('0') << value;
        return ost.str();
    }

private:
    ofstream m_tOLogFile;

    bool m_bEnabled; /**< 标识Log功能是否使能. */
};

extern PokerLog pokerlog; //全局变量

#endif
