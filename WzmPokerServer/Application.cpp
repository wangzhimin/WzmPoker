
#include "Application.h"

#include "GameServerThread.h"
#include "PokerLog.h"

#include <string>
using namespace std;


/**
 * ���캯��.
 */
Application::Application()
    :m_ptGameServerThread(nullptr)
{
    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " ��Ϸ������������ |================" << endl << endl;

    Initialize();
}

/**
 * ��������.
 */
Application::~Application()
{
    Cleanup();

    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " ��Ϸ������ֹͣ�� |================" << endl << endl;
}

/**
 * ��ʼ������.
 */
bool Application::Initialize()
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

    pokerlog << "Application::Initialize OK." << endl;

    return true;
}

/**
 * �������.
 */
void Application::Cleanup()
{
    if (m_ptGameServerThread != nullptr)
    {
        delete m_ptGameServerThread;
        m_ptGameServerThread = nullptr;
    }

    pokerlog << "Application::Cleanup OK." << endl;
}

/**
 * ����ִ������, ���Խ�������ָ��.
 */
int Application::Run()
{
    while(1)
    {
        string strStop;
        getline(cin, strStop);
        if (!strStop.empty())
        {
            cout << "���յ�ָ��:" << strStop << endl;

            if (strStop == "stop") //ֹͣ
            {
                if (m_ptGameServerThread != nullptr)
                {
                    m_ptGameServerThread->Stop();
                }

                cout << "������ֹ. Stopping ......." << endl;
                break;
            }
            else
            {
                cout << "��Чָ��!" << endl;
            }
        }
    }
   
    return 1;
}

