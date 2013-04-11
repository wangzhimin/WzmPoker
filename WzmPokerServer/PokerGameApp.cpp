
#include "PokerGameApp.h"

#include "GameServerThread.h"
#include "PokerLog.h"

#include <string>
using namespace std;


/**
 * 构造函数.
 */
PokerGameApp::PokerGameApp()
    :m_ptGameServerThread(nullptr)
{
    pokerlog.Open();
    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " 游戏服务器启动！ |================" << endl << endl;

    Initialize();
}

/**
 * 析构函数.
 */
PokerGameApp::~PokerGameApp()
{
    Cleanup();

    pokerlog << "================| " << pokerlog.GetTimeStr("-", ":") << " 游戏服务器停止！ |================" << endl << endl;
    pokerlog.Close();
}

/**
 * 初始化操作.
 */
bool PokerGameApp::Initialize()
{
    if (m_ptGameServerThread == nullptr)
    {
        //正式开始游戏线程, 等待用户接入, 每个用户又是一个新的线程来单独处理交互
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
 * 清理操作.
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

