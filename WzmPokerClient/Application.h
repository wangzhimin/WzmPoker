
#ifndef Application_h
#define Application_h

#include "ClientSocket.h"
#include "ThreadObject.h"

#include "d2d.h"
#include "PokerBox.h"
#include "PokerTable.h"


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
    void LoadBitmapResource();
    void LoadBitmapByIDB(int IDB_Start, int IDB_End);
    void UnloadBitmapResource();

    virtual void _process();
    void handleMessage(int msg);
    void onPaint();

    HINSTANCE hInst;
    d2d* graphic;

    bool m_run;
    ClientSocket clientSocket;
    PokerBox pokerBox;
    PokerTable pokerTable;
};


#endif

