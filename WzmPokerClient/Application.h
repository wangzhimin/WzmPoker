
#ifndef Application_h
#define Application_h

#include "ClientSocket.h"
#include "ThreadObject.h"

class d2d;
class Application : public CThreadObject
{
public:
    Application();
    ~Application();

    bool Initialize();
    void CleanUp();
    void Run();
    
    static LRESULT WINAPI StaticMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

    void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void HandleKey(unsigned int keyCode);

private:
    virtual void _process();
    void handleMessage(int msg);
    void onPaint();

    HINSTANCE hInst;
    d2d* graphic;

    bool m_run;
    ClientSocket clientSocket;

};


#endif

