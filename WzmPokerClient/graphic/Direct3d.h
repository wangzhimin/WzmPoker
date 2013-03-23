
#ifndef Direct_3d_h
#define Direct_3d_h

#include <d3d9.h>


class Direct3d
{
public:
    Direct3d();
    ~Direct3d();

    HRESULT Initialize( HWND hWnd );
    void Cleanup();
    void Render();

private:
    LPDIRECT3D9             g_pD3D; //Direct3D对象
    LPDIRECT3DDEVICE9       g_pd3dDevice; //Direct3D设备对象
};

#endif


