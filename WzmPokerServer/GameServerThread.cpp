

#include "GameServerThread.h"

#include "PokerPlayer.h"
#include "PokerLog.h"

#include <iostream>
using namespace std;


GameServerThread::GameServerThread()
    :m_bRun(false),
     server_socket(nullptr)
{
    if (server_socket == nullptr)
    {
        server_socket = new ServerSocket();
        if (server_socket == nullptr)
        {
            pokerlog << "Application::Initialize new ServerSocket fail." << endl;

            return;
        }
    }
}

GameServerThread::~GameServerThread()
{
    if (server_socket != nullptr)
    {
        delete server_socket;
        server_socket = nullptr;
    }
}

bool GameServerThread::Start()
{
    server_socket->Create();

    m_bRun = true;

    return StartThread();
}

void GameServerThread::Stop()
{
    pokerlog << "GameServerThread::Stop() start." << endl;

    m_bRun = false;
    WaitForExit();

    server_socket->Close();
    DestroyUsers();

    pokerlog << "GameServerThread::Stop() ok." << endl;
}

/**
 * 此函数放的是 程序的实际执行任务.
 */
void GameServerThread::_process()
{
    while(m_bRun)
    {
        SOCKET s = server_socket->Accept();
        if (s != INVALID_SOCKET)
        {
            PokerPlayer* user = new PokerPlayer(s);
            vecPokerUsers.push_back(user);
        }
    }
}


void GameServerThread::DestroyUsers()
{
    if (!vecPokerUsers.empty())
    {
        for (vector<PokerPlayer*>::iterator it = vecPokerUsers.begin();
            it != vecPokerUsers.end();
            ++it)
        {
            PokerPlayer* pUser = *it;
            if (pUser != nullptr)
            {
                delete pUser;
            }
        }
        vecPokerUsers.clear();
    }

    pokerlog << "GameServerThread::DestroyUsers() ok." << endl;

}
