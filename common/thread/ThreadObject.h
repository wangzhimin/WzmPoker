#ifndef CTHREAD_OBJECT_H
#define CTHREAD_OBJECT_H

#include <windows.h>

/**
 * �̻߳���, ��Ҫʹ���߳�,ֱ�ӴӴ���̳�, ����һ��Process����.
 */
class CThreadObject
{
public:
    CThreadObject();
    virtual ~CThreadObject();

    bool StartThread();
    void WaitForExit();

    static UINT WINAPI ThreadFunc(void* Param);
    void Process();

private:
    virtual void _process() = 0;

    HANDLE m_hThread;
};

#endif

