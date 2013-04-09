#ifndef APPLICATION_H
#define APPLICATION_H

class GameServerThread;

/**
 * 主程序.
 */
class PokerGameApp
{
public:
    PokerGameApp();
    virtual ~PokerGameApp();

    int Run();

private:
    bool Initialize();
    void Cleanup();

private:
    GameServerThread* m_ptGameServerThread; //服务器主线程
};

#endif