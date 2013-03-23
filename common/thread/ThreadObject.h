#ifndef CTHREAD_OBJECT_H
#define CTHREAD_OBJECT_H

#include <windows.h>

/**
 * 线程基类, 需要使用线程,直接从此类继承, 重载一下Process即可.
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

