

#include "Application.h"
#include "PokerLog.h"



//-----------------------------------------------------------------------------
// Desc: ³ÌÐòÈë¿Ú
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    if (SUCCEEDED(CoInitialize(NULL)))
    {
        Application app;
        bool resApp = app.Initialize();

        if (!resApp)
        {
            return -1;
        }

        app.Run();

        app.CleanUp();
        CoUninitialize();
    }


    return 0;
}

