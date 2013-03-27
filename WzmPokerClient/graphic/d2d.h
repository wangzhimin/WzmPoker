
#ifndef Direct_2D_h
#define Direct_2D_h

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>

#include <vector>
#include <string>
using namespace std;


class d2d
{
public:
    d2d();
    ~d2d();

    HRESULT Initialize( HWND hWnd );
    void CleanUp();

    void InitTextDevice(const wstring fontName = L"ËÎÌו", FLOAT fontSize = 12);

    ID2D1Bitmap* CreateBitmapFromResource(int idPic);
    ID2D1Bitmap* CreateBitmapFromFile(wstring strFileName);


    void BeginDraw();
    void EndDraw();

    void ClearBackground();
    void OnResize(unsigned int width, unsigned int height);

    void ShowPictures();
    void ShowBitmap(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y);
    void ShowText(wstring strText, D2D1_RECT_F position);

private:

    ID2D1Factory* m_pD2DFactory;
    IWICImagingFactory* m_pWICFactory;
    IDWriteFactory* m_pDWriteFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    
    IDWriteTextFormat* m_pTextFormat;
    ID2D1SolidColorBrush* m_pBlackBrush;
};

template<class Interface>
inline void SafeRelease(Interface& pInterfaceToRelease)
{
    if (pInterfaceToRelease != nullptr)
    {
        pInterfaceToRelease->Release();

        pInterfaceToRelease = nullptr;
    }
}



#endif
