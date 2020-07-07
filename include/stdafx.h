#ifndef STDAFX_H_
#define STDAFX_H_

//#define _DEBUG

#include "core/targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdint.h>

#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <d3dcompiler.h>
//#include <D3DX10.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3dcompiler.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct D3DXCOLOR {
    float r; float g; float b; float a;
} D3DXCOLOR;

#endif //STDAFX_H_
