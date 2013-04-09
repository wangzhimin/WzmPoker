
#include "MainWindow.h"

MainWindow::MainWindow()
{
    WidgetWindow::Seed windowCS;

    windowCS.caption = _T( "Wzm Poker Server" );
    windowCS.location = SmartWin::Rectangle( 100, 100, 800, 600);
    createWindow( windowCS );
}

MainWindow::~MainWindow()
{
}

