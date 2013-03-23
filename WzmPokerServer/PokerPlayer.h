
#ifndef Poker_User_h
#define Poker_User_h

#include <WinSock2.h>

#include "ThreadObject.h"

class ServerSocket;

class PokerPlayer : public CThreadObject
{
public:
    PokerPlayer(SOCKET s);
    virtual ~PokerPlayer();

private:
    virtual void _process();
    void HandleMessage(int msg);

    ServerSocket* m_playerSocket;

    bool m_run;
};



#endif


