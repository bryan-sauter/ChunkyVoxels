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
VERTEX SimpleIndexedCube[] =
{
    {-0.5f, -0.5f, 0.5f, red},
    {-0.5f, 0.5f, 0.5f, green},
    {0.5f, 0.5f, 0.5f, blue},
    {0.5f, -0.5f, 0.5f, red},
    {-0.5f, -0.5f, 1.0f, green },
    {-0.5f, 0.5f, 1.0f, blue},
    {0.5f, 0.5f, 1.0f, red},
    {0.5f, -0.5f, 1.0f, green }
};

unsigned int* buildCubeIndex(unsigned int i = 0)
{
	unsigned int* cubeIB = new unsigned int[36];
	//Front
	cubeIB[0] = 0 + (8 * i);
	cubeIB[1] = 1 + (8 * i);
	cubeIB[2] = 2 + (8 * i);
	cubeIB[3] = 0 + (8 * i);
	cubeIB[4] = 2 + (8 * i);
	cubeIB[5] = 3 + (8 * i);
	//Back
	cubeIB[6] = 4 + (8 * i);
	cubeIB[7] = 6 + (8 * i);
	cubeIB[8] = 5 + (8 * i);
	cubeIB[9] = 4 + (8 * i);
	cubeIB[10] = 7 + (8 * i);
	cubeIB[11] = 6 + (8 * i);
	//Left
	cubeIB[12] = 5 + (8 * i);
	cubeIB[13] = 1 + (8 * i);
	cubeIB[14] = 4 + (8 * i);
	cubeIB[15] = 1 + (8 * i);
	cubeIB[16] = 0 + (8 * i);
	cubeIB[17] = 4 + (8 * i);
	//Right
	cubeIB[18] = 3 + (8 * i);
	cubeIB[19] = 2 + (8 * i);
	cubeIB[20] = 6 + (8 * i);
	cubeIB[21] = 3 + (8 * i);
	cubeIB[22] = 6 + (8 * i);
	cubeIB[23] = 7 + (8 * i);
	//Top
	cubeIB[24] = 1 + (8 * i);
	cubeIB[25] = 5 + (8 * i);
	cubeIB[26] = 6 + (8 * i);
	cubeIB[27] = 1 + (8 * i);
	cubeIB[28] = 6 + (8 * i);
	cubeIB[29] = 2 + (8 * i);
	//Bottom
	cubeIB[30] = 4 + (8 * i);
	cubeIB[31] = 0 + (8 * i);
	cubeIB[32] = 3 + (8 * i);
	cubeIB[33] = 4 + (8 * i);
	cubeIB[34] = 3 + (8 * i);
	cubeIB[35] = 7 + (8 * i);

	return cubeIB;
}

#endif //D3D11DECLARES_H_