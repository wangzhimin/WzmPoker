#ifndef APPLICATION_H
#define APPLICATION_H

class GameServerThread;

/**
 * ������.
 */
class PokerGameApp
{
public:
    PokerGameApp();
    virtual ~PokerGameApp();

private:
    bool Initialize();
    void Cleanup();

private:
    GameServerThread* m_ptGameServerThread; //���������߳�
};

#endif