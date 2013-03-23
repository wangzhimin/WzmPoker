
#ifndef Game_Thread_h
#define Game_Thread_h

#include "ServerSocket.h"

#include "ThreadObject.h"

#include <vector>
using namespace std;

class PokerPlayer;

class GameServerThread : public CThreadObject
{
public:
    GameServerThread();
    ~GameServerThread();

    bool Start();
    void Stop();

private:
    virtual void _process();

    void DestroyUsers();

    //成员变量
    bool m_bRun;
    ServerSocket* server_socket;
    vector<PokerPlayer*> vecPokerUsers;
};


#endif

