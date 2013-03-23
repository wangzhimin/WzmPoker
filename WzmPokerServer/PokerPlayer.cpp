
#include "PokerPlayer.h"

#include "PokerMessage.h"
#include "ServerSocket.h"

#include "PokerLog.h"


PokerPlayer::PokerPlayer(SOCKET s)
    :m_playerSocket(nullptr),
     m_run(true)
{
    m_playerSocket = new ServerSocket(s);

    StartThread();
}

PokerPlayer::~PokerPlayer()
{
    m_run = false;

    WaitForExit();

    if (m_playerSocket != nullptr)
    {
        delete m_playerSocket;
        m_playerSocket = nullptr;
    }
}

void PokerPlayer::_process()
{
    char buf[1024] = {0};
    int len = 1024;

    while(m_run)
    {
        if (m_playerSocket->Select() == 1)
        {
            int ret = m_playerSocket->Recv(buf, len, 0);
            if (ret > 0)
            {
                int* p = reinterpret_cast<int*>(buf);
                int msg = *p;
                HandleMessage(msg);
            }
        }
    }
}


void PokerPlayer::HandleMessage(int msg)
{
    char buf[1024] = {0};
    int len = 1024;

    switch(msg)
    {
    case POKER_MSG_LOG_IN:
        {
            pokerlog << "PokerPlayer::Process: recv POKER_MSG_LOG_IN." << endl;

            int* p = reinterpret_cast<int*>(buf);
            *p = POKER_MSG_LOG_ACCEPT;
            m_playerSocket->Send(buf, 4);

            pokerlog << "PokerPlayer::Process: Send POKER_MSG_LOG_ACCEPT." << endl;
        }
        break;

    default:
        break;
    }
}


