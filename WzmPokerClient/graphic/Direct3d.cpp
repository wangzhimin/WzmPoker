
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
// Desc: 初始化Direct3D
//-----------------------------------------------------------------------------
HRESULT Direct3d::InitD3D( HWND hWnd )
{
	//创建Direct3D对象, 该对象用来创建Direct3D设备对象
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

	//设置D3DPRESENT_PARAMETERS结构, 准备创建Direct3D设备对象
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//创建Direct3D设备对象
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

   return S_OK;
}


//-----------------------------------------------------------------------------
// Desc: 释放创建对象
//-----------------------------------------------------------------------------
VOID Direct3d::Cleanup()
{
	//释放Direct3D设备对象
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

	//释放Direct3D对象
    if( g_pD3D != NULL)
        g_pD3D->Release();
}


//-----------------------------------------------------------------------------
// Desc: 渲染图形
//-----------------------------------------------------------------------------
VOID Direct3d::Render()
{
    //清空后台缓冲区
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(45, 50, 170), 1.0f, 0 );
    
    //开始在后台缓冲区绘制图形
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        //在此在后台缓冲区绘制图形
    
        //结束在后台缓冲区渲染图形
        g_pd3dDevice->EndScene();
    }

    //将在后台缓冲区绘制的图形提交到前台缓冲区显示
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

