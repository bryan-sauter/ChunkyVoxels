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
    {-0.5f, -0.5f, -0.5f, red},
    {-0.5f, 0.5f, -0.5f, green},
    {0.5f, 0.5f, -0.5f, blue},
    {0.5f, -0.5f, -0.5f, red},
    {-0.5f, -0.5f, 0.5f, green },
    {-0.5f, 0.5f, 0.5f, blue},
    {0.5f, 0.5f, 0.5f, red},
    {0.5f, -0.5f, 0.5f, green }
};

unsigned int* buildCubeIndex(unsigned int i = 0)
{
	unsigned int* cubeIB = new unsigned int[36];
	//Front
	cubeIB[0] = 0;
	cubeIB[1] = 1;
	cubeIB[2] = 2;
	cubeIB[3] = 0;
	cubeIB[4] = 2;
	cubeIB[5] = 3;
	//Back
	cubeIB[6] = 4;
	cubeIB[7] = 6;
	cubeIB[8] = 5;
	cubeIB[9] = 4;
	cubeIB[10] = 7;
	cubeIB[11] = 6;
	//Left
	cubeIB[12] = 4;
	cubeIB[13] = 5;
	cubeIB[14] = 1;
	cubeIB[15] = 4;
	cubeIB[16] = 1;
	cubeIB[17] = 0;
	//Right
	cubeIB[18] = 3;
	cubeIB[19] = 2;
	cubeIB[20] = 6;
	cubeIB[21] = 3;
	cubeIB[22] = 6;
	cubeIB[23] = 7;
	//Top
	cubeIB[24] = 1;
	cubeIB[25] = 5;
	cubeIB[26] = 6;
	cubeIB[27] = 1;
	cubeIB[28] = 6;
	cubeIB[29] = 2;
	//Bottom
	cubeIB[30] = 4;
	cubeIB[31] = 0;
	cubeIB[32] = 3;
	cubeIB[33] = 4;
	cubeIB[34] = 3;
	cubeIB[35] = 7;

	return cubeIB;
}

#endif //D3D11DECLARES_H_