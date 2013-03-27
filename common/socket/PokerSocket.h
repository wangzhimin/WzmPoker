
#ifndef Poker_Socket_h
#define Poker_Socket_h

#include <winsock2.h>
#include <windows.h>

class PokerSocket
{
public:
    PokerSocket();
    virtual ~PokerSocket();

    void Startup();
    void Cleanup();

    int Select();
    void Send(char data[], int length, int flags=0);
    int Recv(void* buf, int len, int flags = 0);


protected:
    SOCKET m_socket;
    bool m_enable;

private:

};

#endif

