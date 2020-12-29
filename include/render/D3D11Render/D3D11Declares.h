#ifndef D3D11DECLARES_H_
#define D3D11DECLARES_H_

#include "stdafx.h"


//struct can be optimized but for basic development purposes it will remain the same for now
struct COLOR_VERTEX
{
    float x, y, z;
    D3DXCOLOR color;
};

struct TEXTURE_VERTEX
{
    float x, y, z;
    float u, v;
    TEXTURE_VERTEX(float _x, float _y, float _z, float _u, float _v)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->u = _u;
        this->v = _v;
    }
};
D3DXCOLOR red{ 1.0f, 0.0f, 0.0f, 1.0f };
D3DXCOLOR green{ 0.0f, 1.0f, 0.0f, 1.0f };
D3DXCOLOR blue{ 0.0f, 0.0f, 1.0f, 1.0f };
COLOR_VERTEX SimpleIndexedCube[] =
{
    {-0.5f, -0.5f, -0.5f, red},
    {-0.5f, 0.5f, -0.5f, green},
    {0.5f, 0.5f, -0.5f,	 blue},
    {0.5f, -0.5f, -0.5f, red},
    {-0.5f, -0.5f, 0.5f, green },
    {-0.5f, 0.5f, 0.5f,	 blue},
    {0.5f, 0.5f, 0.5f,	 red},
    {0.5f, -0.5f, 0.5f,	 green }
};

unsigned int* buildSimpleColorCubeIndex(unsigned int i = 0)
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

TEXTURE_VERTEX TexturedIndexedCube[] =
{
    // Front Face
    TEXTURE_VERTEX(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(-0.5f,  0.5f, -0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(0.5f,  0.5f, -0.5f, 1.0f, 0.0f),
    TEXTURE_VERTEX(0.5f, -0.5f, -0.5f, 1.0f, 1.0f),

    // Back Face
    TEXTURE_VERTEX(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f),
    TEXTURE_VERTEX(0.5f, -0.5f, 0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(0.5f,  0.5f, 0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(-0.5f,  0.5f, 0.5f, 1.0f, 0.0f),

    // Top Face
    TEXTURE_VERTEX(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(-0.5f, 0.5f,  0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(0.5f, 0.5f,  0.5f, 1.0f, 0.0f),
    TEXTURE_VERTEX(0.5f, 0.5f, -0.5f, 1.0f, 1.0f),

    // Bottom Face
    TEXTURE_VERTEX(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f),
    TEXTURE_VERTEX(0.5f, -0.5f, -0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(-0.5f, -0.5f,  0.5f, 1.0f, 0.0f),

    // Left Face
    TEXTURE_VERTEX(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(-0.5f,  0.5f,  0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(-0.5f,  0.5f, -0.5f, 1.0f, 0.0f),
    TEXTURE_VERTEX(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f),

    // Right Face
    TEXTURE_VERTEX(0.5f, -0.5f, -0.5f, 0.0f, 1.0f),
    TEXTURE_VERTEX(0.5f,  0.5f, -0.5f, 0.0f, 0.0f),
    TEXTURE_VERTEX(0.5f,  0.5f,  0.5f, 1.0f, 0.0f),
    TEXTURE_VERTEX(0.5f, -0.5f,  0.5f, 1.0f, 1.0f),
};

unsigned int* buildTexturedCubeIndex(unsigned int i = 0)
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
	cubeIB[7] = 5;
	cubeIB[8] = 6;
	cubeIB[9] = 4;
	cubeIB[10] = 6;
	cubeIB[11] = 7;
	//Top
	cubeIB[12] = 8;
	cubeIB[13] = 9;
	cubeIB[14] = 10;
	cubeIB[15] = 8;
	cubeIB[16] = 10;
	cubeIB[17] = 11;
	//Bottom
	cubeIB[18] = 12;
	cubeIB[19] = 13;
	cubeIB[20] = 14;
	cubeIB[21] = 12;
	cubeIB[22] = 14;
	cubeIB[23] = 15;
	//Left
	cubeIB[24] = 16;
	cubeIB[25] = 17;
	cubeIB[26] = 18;
	cubeIB[27] = 16;
	cubeIB[28] = 18;
	cubeIB[29] = 19;
	//Right
	cubeIB[30] = 20;
	cubeIB[31] = 21;
	cubeIB[32] = 22;
	cubeIB[33] = 20;
	cubeIB[34] = 22;
	cubeIB[35] = 23;

	return cubeIB;
}

#endif //D3D11DECLARES_H_