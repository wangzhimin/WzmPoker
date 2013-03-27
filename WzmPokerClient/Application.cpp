
#include "Application.h"

#include "PokerMessage.h"
#include "PokerLog.h"
#include "resource.h"


Application::Application()
    :m_run(true),
    graphic(nullptr)
{
}

Application::~Application()
{
}


bool Application::Initialize()
{
    //注册窗口类
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Application::StaticMsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"ClassName", NULL };
    RegisterClassEx( &wc );

    const int WindowWidth = 800;
    const int WindowHeight = 600;

    int DesktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);

    //计算窗口起始坐标
    int StartX = (DesktopWidth - WindowWidth)/2;
    int StartY = (DesktopHeight - WindowHeight)/2;

    //创建窗口
    HWND hWnd = CreateWindow(L"PokerClass", L"WzmPoker", 
                             WS_OVERLAPPEDWINDOW, StartX, StartY, WindowWidth, WindowHeight,
                             NULL, NULL, wc.hInstance, this );

    if (!hWnd)
    {
        return false;
    }

    graphic = new d2d();

    HRESULT hr = graphic->Initialize( hWnd ); //初始化图形系统
    if( FAILED(hr) )
    {
        MessageBox(hWnd, L"graphic Initialize fail.", L"error", 0);
        return false;
    }
    for (int index = IDB_PNG102; index <= IDB_PNG114; ++index)
    {
        ID2D1Bitmap* pBitmap = graphic->CreateBitmapFromResource(index);
        if (pBitmap != nullptr)
        {
            m_VecBitmap.push_back(pBitmap);
        }
    }
    //显示主窗口
    ShowWindow( hWnd, SW_SHOWDEFAULT );
    UpdateWindow( hWnd );

    clientSocket.Create();
    clientSocket.Connect();

    m_run = true;

    hInst = wc.hInstance;

    pokerlog << "Application::Initialize() ok." << endl;

    return true;
}

void Application::CleanUp()
{
    m_run = false;

    clientSocket.Close();

    for(auto it = m_VecBitmap.begin(); it != m_VecBitmap.end(); ++it)
    {
        SafeRelease(*it);
    }
    m_VecBitmap.clear();


    graphic->CleanUp();
    UnregisterClass( L"PokerClass", hInst );

    pokerlog << "Application::CleanUp() ok." << endl;
}

void Application::Run()
{
    //进入消息循环
    MSG msg;
    ZeroMemory( &msg, sizeof(msg) );
    //while( msg.message != WM_QUIT )
    //{
    //    if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
    while (GetMessage(&msg, NULL, 0, 0))

    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    //}
}


LRESULT WINAPI Application::StaticMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    if (uMsg == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Application *pApp = (Application *)pcs->lpCreateParams;

        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToUlong(pApp));
    }
    else
    {
        Application *pApp = reinterpret_cast<Application *>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA)));

        if (pApp != nullptr)
        {
            pApp->MsgProc(hWnd, uMsg, wParam, lParam);
        }
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void Application::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg )
    {
    case WM_DESTROY:
        CleanUp();
        PostQuitMessage( 0 );
        return;

    case WM_PAINT:
        onPaint();

        ValidateRect( hWnd, NULL );
        return;

    case WM_SIZE:
        if (graphic != nullptr)
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            graphic->OnResize(width, height);
        }
        break;

    case WM_CHAR:
        HandleKey(wParam);
        break;
    }
}

//响应 keyboard
void Application::HandleKey(unsigned int keyCode)
{
    switch( keyCode )
    {
    case 'l':
        {
            if (!clientSocket.isConnected())
            {
                break;
            }

            char buff[1024] = {0};
            int* p = reinterpret_cast<int*>(buff);
            *p = POKER_MSG_LOG_IN;

            clientSocket.Send(buff, 4);

            pokerlog << "Client Send POKER_MSG_LOG_IN." << endl;
        }
        break;
    }
}

void Application::_process()
{
    char buf[1024] = {0};
    int len = 1024;

    while(m_run)
    {
        if (clientSocket.Select() == 1)
        {
            int ret = clientSocket.Recv(buf, len, 0);
            pokerlog << "clientSocket.Recv, ret = " << ret << endl;
            if (ret > 0)
            {
                int* p = reinterpret_cast<int*>(buf);
                int msg = *p;
                handleMessage(msg);
            }
        }
    }
}

//响应 socket message
void Application::handleMessage(int msg)
{
    pokerlog << "Application::handleMessage, msg = " << msg << endl;

    switch(msg)
    {
    case POKER_MSG_LOG_ACCEPT:
        pokerlog << "Application::handleMessage, POKER_MSG_LOG_ACCEPT." << endl;
        break;
    }
}


void Application::onPaint()
{
    if (graphic != nullptr)
    {
        graphic->BeginDraw();

        graphic->ClearBackground();

        FLOAT left = 20;
        FLOAT top = 300;

        FLOAT deltaX = 50;
        FLOAT deltaY = 0;
        for(auto it = m_VecBitmap.begin(); it != m_VecBitmap.end(); ++it)
        {
            if ((*it) != nullptr)
            {
                graphic->ShowBitmap((*it), left, top);

                left += deltaX;
                top  += deltaY;
            }
        }
        D2D1_RECT_F pos = {100, 100, 300, 300};

        graphic->ShowText( L"Hello, World!", pos);

        graphic->EndDraw();
    }
}



