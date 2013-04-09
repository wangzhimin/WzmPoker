
#ifndef Main_Window_h
#define Main_Window_h

#include "SmartWin.h"
using namespace SmartWin;


class MainWindow : public WidgetFactory< WidgetWindow, MainWindow >
{
public:
    MainWindow();
    ~MainWindow();
};

#endif

