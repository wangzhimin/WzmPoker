
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
    void Render();
    void CleanUp();
    void OnResize(unsigned int width, unsigned int height);

    void LoadPicures();

private:
    bool CreateBitmapFromResource(int idPng);
    bool CreateBitmapFromFile(wstring strFileName);
    void InitTextDevice();

    ID2D1Factory* m_pD2DFactory;
    IWICImagingFactory* m_pWICFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;

    vector<ID2D1Bitmap*> m_VecBitmap;

    IDWriteFactory* m_pDWriteFactory;
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
