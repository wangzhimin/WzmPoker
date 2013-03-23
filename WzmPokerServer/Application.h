#ifndef APPLICATION_H
#define APPLICATION_H

class GameServerThread;

/**
 * ������.
 */
class Application
{
public:
    Application();
    virtual ~Application();

    int Run();

private:
    bool Initialize();
    void Cleanup();

private:
    GameServerThread* m_ptGameServerThread; //���������߳�
};

#endif