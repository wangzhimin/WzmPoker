
#ifndef Client_Socket_h
#define Client_Socket_h

#include "PokerSocket.h"


class ClientSocket : public PokerSocket
{
public:
    ClientSocket();
    virtual ~ClientSocket();

    void Create();
    void Close();
    
    bool Connect();
    bool isConnected() { return connected; }

private:
    bool connected;
};

#endif

