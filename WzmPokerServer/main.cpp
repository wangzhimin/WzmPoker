
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
    new MainWindow();

    app.run();

    return 0;
}
