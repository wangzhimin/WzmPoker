
#include "ThreadObject.h"

#include <process.h>

/**
 * ���캯��.
 */
CThreadObject::CThreadObject()
: m_hThread(NULL)
{
}

/**
 * ��������.
 */
CThreadObject::~CThreadObject()
{
}

/**
 * �����߳�.
 */
bool CThreadObject::StartThread()
{
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, 0);

    return (m_hThread != NULL);
}

/**
 * �����߳�.
 */
void CThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, 1000);
    CloseHandle(m_hThread);

    //_endthreadex((unsigned int)m_hThread);
}

/**
 * �ص�����.
 */
UINT WINAPI CThreadObject::ThreadFunc(void* Param)
{
    CThreadObject* ptThis = reinterpret_cast<CThreadObject*>(Param);
    ptThis->Process();

    return 0;
}

/**
 * �߳�ִ������, ���������ຯ��.
 */
void CThreadObject::Process()
{
    _process();
}