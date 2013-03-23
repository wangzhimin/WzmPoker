
#include "ThreadObject.h"

#include <process.h>

/**
 * 构造函数.
 */
CThreadObject::CThreadObject()
: m_hThread(NULL)
{
}

/**
 * 析构函数.
 */
CThreadObject::~CThreadObject()
{
}

/**
 * 开启线程.
 */
bool CThreadObject::StartThread()
{
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, 0);

    return (m_hThread != NULL);
}

/**
 * 结束线程.
 */
void CThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, 1000);
    CloseHandle(m_hThread);

    //_endthreadex((unsigned int)m_hThread);
}

/**
 * 回调函数.
 */
UINT WINAPI CThreadObject::ThreadFunc(void* Param)
{
    CThreadObject* ptThis = reinterpret_cast<CThreadObject*>(Param);
    ptThis->Process();

    return 0;
}

/**
 * 线程执行主体, 调用派生类函数.
 */
void CThreadObject::Process()
{
    _process();
}