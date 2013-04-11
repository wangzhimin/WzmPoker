
#include <iostream>
using namespace std;

#include "PokerLog.h"
#include "PokerGameApp.h"
#include "MainWindow.h"


int SmartWinMain(Application & app)
{
    /*try
    {
        PokerGameApp app;
        app.Run();
    }
    catch(exception& ex)
    {
        pokerlog << "捕捉到异常：" << ex.what() << endl;
    }

    cout << endl << "程序执行完毕！ " << endl << endl;
    cout << "请按 Enter 键退出..." << endl;

    cin.get();*/
    MainWindow* mainWin = new MainWindow();
    MainWindow::WidgetButtonPtr startButton = mainWin->createButton();

    startButton->setBounds(10, 10, 100, 50);
    startButton->setText("start");
    startButton->onClicked(&MainWindow::buttonClicked);

    app.run();

    return 0;
}
