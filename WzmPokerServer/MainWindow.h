
#ifndef Main_Window_h
#define Main_Window_h

#include "SmartWin.h"
using namespace SmartWin;

class PokerGameApp;
class MainWindow : public WidgetFactory< WidgetWindow, MainWindow >
{
public:
    MainWindow();
    ~MainWindow();

	void buttonClicked( WidgetButtonPtr btn );

private:
    PokerGameApp* gameApp;
};

#endif

