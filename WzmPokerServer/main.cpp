
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
        pokerlog << "捕捉到异常：" << ex.what() << endl;
    }

    cout << endl << "程序执行完毕！ " << endl << endl;
    cout << "请按 Enter 键退出..." << endl;

    cin.get();
}
