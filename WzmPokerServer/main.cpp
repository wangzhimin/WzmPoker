
#include <iostream>
using namespace std;

#include "PokerLog.h"
#include "Application.h"

int main()
{
    try
    {
        Application app;
        app.Run();
    }
    catch(exception& ex)
    {
        pokerlog << "��׽���쳣��" << ex.what() << endl;
    }

    cout << endl << "����ִ����ϣ� " << endl << endl;
    cout << "�밴 Enter ���˳�..." << endl;

    cin.get();
}
