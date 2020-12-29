#ifndef D3D11TEXTUREMANAGER_H_
#define D3D11TEXTUREMANAGER_H_

#include "stdafx.h"
#include <unordered_map>

#include "render/D3D11Render/D3D11TextureHandle.h"

class D3D11TextureManager
{
private:
    Texture_ID m_nextHandle;

    unordered_map<Texture_ID, D3D11TextureHandle> m_umTextureMap;

    Texture_ID getTexture(const wchar_t* textureFilePath);
public:
    D3D11TextureManager(void);

    void initialize(ID3D11Device* pDevice, ID3D11ShaderResourceView** m_pResourceView);
    Texture_ID loadTexture(ID3D11Device* pDevice, ID3D11ShaderResourceView** m_pResourceView, const wchar_t* textureFilePath);
    void shutdown(void);

    ID3D11Resource* getTexture(Texture_ID textureID);
    ID3D11SamplerState* getSamplerState(Texture_ID textureID);
};

#endif //D3D11TEXTUREMANAGER_H_