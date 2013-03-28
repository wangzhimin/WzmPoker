
#include "ClientSocket.h"
#include "Exception.h"

#include "PokerLog.h"


ClientSocket::ClientSocket()
    :PokerSocket(),
     connected(false)
{
}

ClientSocket::~ClientSocket()
{
}

/**
 * ´´½¨Ì×½Ó×Ö.SOCK_STREAM IPPROTO_TCP
 */
void ClientSocket::Create()
{
    /* 
    WSA_FLAG_OVERLAPPED, This flag causes an overlapped socket to be created.
    Overlapped sockets can utilize WSASend, WSASendTo, WSARecv, WSARecvFrom, 
    and WSAIoctl for overlapped I/O operations, which allow multiple operations 
    to be initiated and in progress simultaneously. 
    */
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_socket == INVALID_SOCKET)
    {
    }

    pokerlog << "ClientSocket::Create() ok." << endl;
}

void ClientSocket::Close()
{
    shutdown(m_socket, SD_SEND);

    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }

    connected = false;

    pokerlog << "ClientSocket::Close() ok." << endl;
}

void ClientSocket::Connect()
{
    if (!m_enable)
    {
        return;
    }

	LPHOSTENT lpHost = gethostbyname("192.168.100.102");
    if (lpHost == NULL)
    {
        return;
    }

    struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = *((u_long FAR*)(lpHost->h_addr));
	server.sin_port = htons(1234);

    int resConnect = connect(m_socket, (LPSOCKADDR)&server, sizeof(SOCKADDR));
    if (resConnect == SOCKET_ERROR)
    {
        int errorno = WSAGetLastError();
        pokerlog << "ClientSocket::Connect() connect fail, ErrNo = " << errorno << endl;

        return;
    }
    
    connected = true;

    pokerlog << "ClientSocket::Connect() ok." << endl;

    return;
}


