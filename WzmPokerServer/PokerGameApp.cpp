
#include "PokerGameApp.h"

#include "GameServerThread.h"
#include "PokerLog.h"

#include <string>
using namespace std;


/**
 * ���캯��.
 */
PokerGameApp::PokerGameApp()
    :m_ptGameServerThread(nullptr)
{
    pokerlog.Open();
    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " ��Ϸ������������ |================" << endl << endl;

    Initialize();
}

/**
 * ��������.
 */
PokerGameApp::~PokerGameApp()
{
    Cleanup();

    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " ��Ϸ������ֹͣ�� |================" << endl << endl;
    pokerlog.Close();
}

/**
 * ��ʼ������.
 */
bool PokerGameApp::Initialize()
{
    if (m_ptGameServerThread == nullptr)
    {
        //��ʽ��ʼ��Ϸ�߳�, �ȴ��û�����, ÿ���û�����һ���µ��߳�������������
        m_ptGameServerThread = new GameServerThread();
        if (m_ptGameServerThread == nullptr)
        {
            return false;
        }
        m_ptGameServerThread->Start();
    }

    pokerlog << "PokerGameApp::Initialize OK." << endl;

    return true;
}

/**
 * �������.
 */
void PokerGameApp::Cleanup()
{
    if (m_ptGameServerThread != nullptr)
    {
        m_ptGameServerThread->Stop();

        delete m_ptGameServerThread;
        m_ptGameServerThread = nullptr;
    }

    pokerlog << "PokerGameApp::Cleanup OK." << endl;
}

