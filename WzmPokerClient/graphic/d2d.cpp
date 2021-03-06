
#include "d2d.h"

#include "PokerLog.h"

d2d::d2d()
    :m_pD2DFactory(nullptr),
     m_pRenderTarget(nullptr),
     m_pWICFactory(nullptr),
     m_pDWriteFactory(nullptr),
     m_pTextFormat(nullptr),
     m_pBlackBrush(nullptr)
{
}

d2d::~d2d()
{
}

HRESULT d2d::Initialize( HWND hWnd )
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    if (FAILED(hr))
    {
        return S_FALSE;
    }

    RECT rc;
    GetClientRect(hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &m_pRenderTarget) ;
    if (FAILED(hr))
    {
        return S_FALSE;
    }
    
    InitBitmapDevice();
    InitTextDevice();

    return S_OK;
}

void d2d::CleanUp()
{
    SafeRelease(m_pBlackBrush);
    SafeRelease(m_pTextFormat);
    SafeRelease(m_pRenderTarget);
    SafeRelease(m_pDWriteFactory);
    SafeRelease(m_pWICFactory);
    SafeRelease(m_pD2DFactory);
}

ID2D1Bitmap* d2d::CreateBitmapFromResource(int idPic, int destinationWidth, int destinationHeight)
{
    // Locate the resource.
    HRSRC imageResHandle = FindResource(NULL, MAKEINTRESOURCE(idPic), L"PNG");
    if (imageResHandle == nullptr)
    {
        return nullptr;
    }

    // Load the resource.
    HGLOBAL imageResDataHandle = LoadResource(NULL, imageResHandle);
    //If hModule is NULL, the system loads the resource from the module that was used to create the current process

    HRESULT hr = imageResDataHandle ? S_OK : E_FAIL;
    if (FAILED(hr))
    {
        return nullptr;
    }

    // Lock it to get a system memory pointer.
    void* pImageFile = LockResource(imageResDataHandle);
    if (pImageFile == nullptr)
    {
        return nullptr;
    }
        
    // Calculate the size.
    DWORD imageFileSize = SizeofResource(NULL, imageResHandle);
    if (imageFileSize == 0)
    {
        return nullptr;
    }
    
    // Create a WIC stream to map onto the memory.
    IWICStream *pStream = nullptr;

    hr = m_pWICFactory->CreateStream(&pStream);
    if (FAILED(hr))
    {
        return nullptr;
    }
        
    // Initialize the stream with the memory pointer and size.
    hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize);
    if (FAILED(hr))
    {
        return nullptr;
    }
    
    // Create a decoder for the stream.
    IWICBitmapDecoder *pDecoder = nullptr;

    hr = m_pWICFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
    if (FAILED(hr))
    {
        return nullptr;
    }
    
    // Create the initial frame.
    IWICBitmapFrameDecode *pSource = nullptr;

    hr = pDecoder->GetFrame(0, &pSource);
    if (FAILED(hr))
    {
        return nullptr;
    }

    // Convert the image format to 32bppPBGRA
    // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
    IWICFormatConverter *pConverter = NULL;

    hr = m_pWICFactory->CreateFormatConverter(&pConverter);
    if (FAILED(hr))
    {
        return nullptr;
    }

    // If a new width or height was specified, create an
    // IWICBitmapScaler and use it to resize the image.
    if (destinationWidth != 0 || destinationHeight != 0)
    {
        UINT originalWidth, originalHeight;
        hr = pSource->GetSize(&originalWidth, &originalHeight);
        if (SUCCEEDED(hr))
        {
            if (destinationWidth == 0)
            {
                FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
                destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
            }
            else if (destinationHeight == 0)
            {
                FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
                destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
            }

            IWICBitmapScaler *pScaler = nullptr;

            hr = m_pWICFactory->CreateBitmapScaler(&pScaler);
            if (SUCCEEDED(hr))
            {
                hr = pScaler->Initialize(pSource,destinationWidth,destinationHeight,WICBitmapInterpolationModeCubic);
                if (SUCCEEDED(hr))
                {
                    hr = pConverter->Initialize(pScaler,GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0.f,WICBitmapPaletteTypeMedianCut);
                }
            }
            SafeRelease(pScaler);
        }
    }
    else
    {
        hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
    }
    if (FAILED(hr))
    {
        return nullptr;
    }

    //create a Direct2D bitmap from the WIC bitmap.
    ID2D1Bitmap* resBitmap = nullptr;

    hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &resBitmap);
    if (FAILED(hr) || resBitmap == nullptr)
    {
        return nullptr;
    }

    SafeRelease(pDecoder);
    SafeRelease(pSource);
    SafeRelease(pStream);
    SafeRelease(pConverter);

    pokerlog << "CreateBitmapFromResource " << idPic << " OK." << endl;
    return resBitmap;
}

//从一个文件加载图片
ID2D1Bitmap* d2d::CreateBitmapFromFile(wstring strFileName)
{
    IWICBitmapDecoder *pDecoder = nullptr;
    HRESULT hr = m_pWICFactory->CreateDecoderFromFilename(strFileName.c_str(), NULL, GENERIC_READ,
                                                          WICDecodeMetadataCacheOnLoad, //enum WICDecodeOptions
                                                          &pDecoder);

    if (FAILED(hr))
    {
        return nullptr;
    }

     // Create the initial frame.
    IWICBitmapFrameDecode *pSource = nullptr;
    hr = pDecoder->GetFrame(0, &pSource);
    if (FAILED(hr))
    {
        return nullptr;
    }

    //转换器
    IWICFormatConverter *pConverter = nullptr;
    hr = m_pWICFactory->CreateFormatConverter(&pConverter);
    if (FAILED(hr))
    {
        return nullptr;
    }

    hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
                                NULL, 0.f, WICBitmapPaletteTypeMedianCut);
 
    if (FAILED(hr))
    {
        return nullptr;
    }
    
    // Create a Direct2D bitmap from the WIC bitmap.
    ID2D1Bitmap* picBitmap = nullptr;
    hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &picBitmap);
    if (FAILED(hr))
    {
        return nullptr;
    }

    SafeRelease(pDecoder);
    SafeRelease(pSource);
    SafeRelease(pConverter);

    return picBitmap;
}

void d2d::BeginDraw()
{
    m_pRenderTarget->BeginDraw();
}

void d2d::EndDraw()
{
    HRESULT hr = m_pRenderTarget->EndDraw();

    if (FAILED(hr))
    {
        MessageBox(NULL, L"EndDraw failed!", L"Error", 0) ;

        return ;
    }
}

void d2d::ClearBackground()
{
    // Clear background
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void d2d::ShowBitmap(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y)
{
    D2D1_SIZE_F size = pBitmap->GetSize() ;

    m_pRenderTarget->DrawBitmap(pBitmap, D2D1::RectF(x, y, x + size.width, y + size.height)) ;
}


void d2d::ShowText(wstring strText, D2D1_RECT_F position)
{
    m_pRenderTarget->DrawText(strText.c_str(), strText.size(),
            m_pTextFormat, position, m_pBlackBrush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

void d2d::OnResize(unsigned int width, unsigned int height)
{
    if (m_pRenderTarget != nullptr)
    {
        D2D1_SIZE_U size = {width, height};

        // Note: This method can fail, but it's okay to ignore the
        // error here -- it will be repeated on the next call to
        // EndDraw.
        m_pRenderTarget->Resize(size);
    }
}

bool d2d::InitBitmapDevice()
{
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void d2d::InitTextDevice(const wstring fontName, FLOAT fontSize)
{
    if (m_pD2DFactory == nullptr)
    {
        return;
    }
    
    // Create a DirectWrite factory.
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
    if (FAILED(hr) || m_pDWriteFactory == nullptr)
    {
        return;
    }

    // Create a DirectWrite text format object.
    hr = m_pDWriteFactory->CreateTextFormat(
            fontName.c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &m_pTextFormat);
    
    if (FAILED(hr) || m_pTextFormat == nullptr)
    {
        return;
    }

    // Center the text horizontally and vertically.
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);

    pokerlog << "InitTextDevice OK." << endl;
}


