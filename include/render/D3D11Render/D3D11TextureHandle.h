#ifndef D3D11TEXTUREHANDLE_H_
#define D3D11TEXTUREHANDLE_H_

#include "stdafx.h"

typedef size_t Texture_ID;
static const Texture_ID defaultTextureID    = 0u;
static const Texture_ID maxTextureID        = SIZE_MAX;

struct D3D11TextureHandle
{
    const wchar_t* m_cFilePath;
    Texture_ID          m_uiTextureID;
    unsigned int        m_uiRefCount;
    unsigned int        m_uiWidth;
    unsigned int        m_uiHeight;
    ID3D11Resource* m_pTexture;
    ID3D11SamplerState* m_pSampleState;

    D3D11TextureHandle() :
        m_cFilePath(nullptr),
        m_uiTextureID(defaultTextureID),
        m_uiRefCount(1u),
        m_uiWidth(0u),
        m_uiHeight(0u),
        m_pTexture(nullptr),
        m_pSampleState(nullptr)
    {
        //default constructor
    }

    D3D11TextureHandle(Texture_ID textureID, const wchar_t* filePath)
    {
        m_cFilePath     = filePath;
        m_uiTextureID   = textureID;
        m_uiRefCount    = 1u;
        m_uiWidth       = 0u;
        m_uiHeight      = 0u;
        m_pTexture      = nullptr;
        m_pSampleState  = nullptr;
    }
};

#endif //D3D11TEXTUREHANDLE_H_