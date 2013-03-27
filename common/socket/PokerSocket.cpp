
#include "PokerSocket.h"

#include "Exception.h"


PokerSocket::PokerSocket()
    :m_socket(INVALID_SOCKET),
     m_enable(true)
{
    Startup();
}

PokerSocket::~PokerSocket()
{
    Cleanup();
}

void PokerSocket::Startup()
{
    WORD wVersionRequested = MAKEWORD(2, 2); //��������Ϊsocket2.2

    WSADATA wsaData;   //����װ��socket�汾�ı���
    int err = WSAStartup(wVersionRequested, &wsaData);   //װ��socket2.0֧��

    if (0 != err)//�ж��Ƿ�װ�سɹ�
    {
        throw socket_error("Socket Start Fail.");

        return;   
    }   

    if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)//�жϰ汾�ţ��Ƿ�Ͷ����һ��
    {   
        WSACleanup();   //�������⣬ж��֧�֣����������򷵻�-1
        return;     
    }
}

void PokerSocket::Cleanup()
{
    WSACleanup();
}

int PokerSocket::Select()
{
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(m_socket, &fs);

    timeval tv = {0,5000}; //timeout

    return select(1, &fs, NULL, NULL, &tv);
}

void PokerSocket::Send(char data[], int length, int flags)
{
    int nRet = send(m_socket, data, length, flags);

	if(nRet == SOCKET_ERROR)
	{
		throw socket_error("Socket send fail.");

        return;
	}
}


int PokerSocket::Recv(void* buf, int len, int flags)
{
    if (m_socket == INVALID_SOCKET)
    {
        return 0;
    }

    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(m_socket, &fs);

    timeval tv = {0, 5000};
    if (select(1, &fs, NULL, NULL, &tv) == 1)
    {
        return recv(m_socket, static_cast<char*>(buf), len, flags);
    }
    return 0;
}


