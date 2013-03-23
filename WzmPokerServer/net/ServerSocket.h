
#ifndef Poker_SOCKET_H
#define Poker_SOCKET_H

#include "PokerSocket.h"


class ServerSocket : public PokerSocket
{
public:
    ServerSocket();
    ServerSocket(SOCKET playerSocket);

    virtual ~ServerSocket();

    void Create();
    void Close();

    SOCKET Accept();

};

#endif

