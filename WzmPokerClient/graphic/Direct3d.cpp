
#include "Direct3d.h"

#pragma comment(lib, "d3d9.lib")

Direct3d::Direct3d()
    :g_pD3D(NULL),
     g_pd3dDevice(NULL)
{
}

Direct3d::~Direct3d()
{
}

//-----------------------------------------------------------------------------
// Desc: ��ʼ��Direct3D
//-----------------------------------------------------------------------------
HRESULT Direct3d::InitD3D( HWND hWnd )
{
	//����Direct3D����, �ö�����������Direct3D�豸����
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

	//����D3DPRESENT_PARAMETERS�ṹ, ׼������Direct3D�豸����
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//����Direct3D�豸����
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

   return S_OK;
}


//-----------------------------------------------------------------------------
// Desc: �ͷŴ�������
//-----------------------------------------------------------------------------
VOID Direct3d::Cleanup()
{
	//�ͷ�Direct3D�豸����
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

	//�ͷ�Direct3D����
    if( g_pD3D != NULL)
        g_pD3D->Release();
}


//-----------------------------------------------------------------------------
// Desc: ��Ⱦͼ��
//-----------------------------------------------------------------------------
VOID Direct3d::Render()
{
    //��պ�̨������
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(45, 50, 170), 1.0f, 0 );
    
    //��ʼ�ں�̨����������ͼ��
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        //�ڴ��ں�̨����������ͼ��
    
        //�����ں�̨��������Ⱦͼ��
        g_pd3dDevice->EndScene();
    }

    //���ں�̨���������Ƶ�ͼ���ύ��ǰ̨��������ʾ
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

