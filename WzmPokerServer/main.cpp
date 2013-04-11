
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
        pokerlog << "��׽���쳣��" << ex.what() << endl;
    }

    cout << endl << "����ִ����ϣ� " << endl << endl;
    cout << "�밴 Enter ���˳�..." << endl;

    cin.get();*/
    MainWindow* mainWin = new MainWindow();
    MainWindow::WidgetButtonPtr startButton = mainWin->createButton();

    startButton->setBounds(10, 10, 100, 50);
    startButton->setText("start");
    startButton->onClicked(&MainWindow::buttonClicked);

    app.run();

    return 0;
}
