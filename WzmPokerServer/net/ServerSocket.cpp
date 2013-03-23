
#include "ServerSocket.h"

#include "Exception.h"
#include "PokerLog.h"


ServerSocket::ServerSocket()
    :PokerSocket()
{
}

/**
 * 接收到Client时，创建新的serversocket
 */
ServerSocket::ServerSocket(SOCKET playerSocket)
{
    m_socket = playerSocket;
}

ServerSocket::~ServerSocket()
{
    Cleanup();
}


/**
 * 创建套接字.SOCK_STREAM IPPROTO_TCP
 */
void ServerSocket::Create()
{
    /* 
    WSA_FLAG_OVERLAPPED, This flag causes an overlapped socket to be created.
    Overlapped sockets can utilize WSASend, WSASendTo, WSARecv, WSARecvFrom, 
    and WSAIoctl for overlapped I/O operations, which allow multiple operations 
    to be initiated and in progress simultaneously. 
    */
    //m_socket = WSASocket (PF_INET, socketType, protocolType, NULL, 0, WSA_FLAG_OVERLAPPED);
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_socket == INVALID_SOCKET)
    {
        throw socket_error("socket fail");
        return;
    }

    struct sockaddr_in local;

	local.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY允许服务器应用监听主机计算机上面每个网络接口上的客户机活动
	local.sin_family = AF_INET;
	local.sin_port = htons(1234);

    int res = bind(m_socket, (struct sockaddr*)&local, sizeof(local)); //将指定的套接字同一个已知地址绑定到一起
	if (res == INVALID_SOCKET)
	{
        throw socket_error("bind fail");

		closesocket(m_socket);
		return;
	}

    int ret = listen(m_socket, 5);
	if(ret != 0) //将socket置入监听模式，指示等候进入连接
	{
        throw socket_error("listen fail");

		closesocket(m_socket);
		return;
	}

    pokerlog << "ServerSocket::Create OK." << endl;
}

void ServerSocket::Close()
{
    shutdown(m_socket, SD_SEND);

    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }

    pokerlog << "ServerSocket::Close OK." << endl;
}

SOCKET ServerSocket::Accept()
{
    if (m_socket == INVALID_SOCKET)
    {
        return INVALID_SOCKET;
    }

    sockaddr_in addr;
	int iAddrSize = sizeof(addr);
    
	SOCKET sClient = accept(m_socket, (sockaddr*)&addr, &iAddrSize);
    pokerlog << "ServerSocket::Accept(), sClient = " << sClient << endl;

	if (sClient == SOCKET_ERROR)
	{
		closesocket(sClient);
		return INVALID_SOCKET;
	}

    pokerlog << "ServerSocket::Accept(), IP:" << inet_ntoa(addr.sin_addr) << endl;

    return sClient;
}
