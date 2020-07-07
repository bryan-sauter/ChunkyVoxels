#ifndef D3D11DECLARES_H_
#define D3D11DECLARES_H_

#include "stdafx.h"

struct VERTEX
{
    float x, y, z;
    D3DXCOLOR color;
};
D3DXCOLOR red{ 1.0f, 0.0f, 0.0f, 1.0f };
D3DXCOLOR green{ 0.0f, 1.0f, 0.0f, 1.0f };
D3DXCOLOR blue{ 0.0f, 0.0f, 1.0f, 1.0f };
VERTEX SimpleTriangle[] =
{
    {0.0f, 0.5f, 0.0f, red},
    {0.45f, -0.5, 0.0f, green},
    {-0.45f, -0.5f, 0.0f, blue}
};

#endif //D3D11DECLARES_H_