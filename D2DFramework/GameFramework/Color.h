#pragma once
#include <d3dx9math.h>
class Color :
    public D3DXCOLOR
{
public:
    Color(D3DXCOLOR r);
    Color(float a, float r, float g, float b);

public:
    static DWORD Red() {
        return  D3DCOLOR_ARGB(255, 255, 0, 0);
    }
};

