
#include "MainWindow.h"

#include "PokerGameApp.h"


MainWindow::MainWindow()
    :gameApp(nullptr)
{
    WidgetWindow::Seed windowCS;

    windowCS.caption = _T( "Wzm Poker Server" );
    windowCS.location = SmartWin::Rectangle( 100, 100, 800, 600);
    createWindow( windowCS );
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonClicked( WidgetButtonPtr btn )
{
    if (gameApp == nullptr)
    {
        gameApp = new PokerGameApp();

        btn->setText("stop");

        return;
    }

    delete gameApp;
    gameApp = nullptr;

    btn->setText("start");
}

