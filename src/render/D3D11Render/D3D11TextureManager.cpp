#include "render/D3D11Render/D3D11TextureManager.h"

#include "helpers/HResultHelpers.h"
#include <DDSTextureLoader.h>


D3D11TextureManager::D3D11TextureManager(void) :
    m_nextHandle(defaultTextureID)
{
}

void D3D11TextureManager::initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
    loadTexture(pDevice, pDeviceContext, L"./resource/render/Texture/sample.dds"); //need to load the default texture which would move the next handle
}

Texture_ID D3D11TextureManager::loadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const wchar_t* textureFilePath)
{
    if (!textureFilePath)
    {
        return defaultTextureID;
    }

    Texture_ID existingID = getTexture(textureFilePath);

    if (existingID != defaultTextureID)
    {
        m_umTextureMap.at(existingID).m_uiRefCount++;
        return existingID;
    }
    size_t currentHandle = m_nextHandle;
    m_umTextureMap[currentHandle] = D3D11TextureHandle(m_nextHandle, textureFilePath);
    try
    {
        ThrowIfFailed(DirectX::CreateDDSTextureFromFile(pDevice, textureFilePath, 
            &(m_umTextureMap[currentHandle].m_pTexture), &(m_umTextureMap[currentHandle].m_pSRV) ));

        if (m_umTextureMap[currentHandle].m_pTexture)
        {
            D3D11_TEXTURE2D_DESC desc;
            ((ID3D11Texture2D*)m_umTextureMap[currentHandle].m_pTexture)->GetDesc(&desc);

            m_umTextureMap[currentHandle].m_uiHeight = desc.Height;
            m_umTextureMap[currentHandle].m_uiWidth = desc.Width;

            m_nextHandle++;
        }

        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        ThrowIfFailed(pDevice->CreateSamplerState(&sampDesc, &(m_umTextureMap[currentHandle].m_pSampleState)));
    }
    catch (HrException hr)
    {
        currentHandle = defaultTextureID;
    }

    return m_umTextureMap[currentHandle].m_uiTextureID;
}

void D3D11TextureManager::shutdown(void)
{
}

ID3D11Resource* D3D11TextureManager::getTexture(Texture_ID textureID)
{
    return textureID < m_nextHandle ? m_umTextureMap[textureID].m_pTexture : m_umTextureMap[defaultTextureID].m_pTexture;
}

ID3D11ShaderResourceView* D3D11TextureManager::getSRV(Texture_ID textureID)
{
    return textureID < m_nextHandle ? m_umTextureMap[textureID].m_pSRV : m_umTextureMap[defaultTextureID].m_pSRV;;
}

ID3D11SamplerState* D3D11TextureManager::getSamplerState(Texture_ID textureID)
{
    return textureID < m_nextHandle ? m_umTextureMap[textureID].m_pSampleState : m_umTextureMap[defaultTextureID].m_pSampleState;;
}

Texture_ID D3D11TextureManager::getTexture(const wchar_t* textureFilePath)
{
    //loop through the texture map
    for (auto const& valuePair : m_umTextureMap)
    {
        //check if the file path/name is the same
        if (wcscmp(textureFilePath, valuePair.second.m_cFilePath) == 0)
        {
            //return the texture ID, caller is responsible for ref counting
            return valuePair.second.m_uiTextureID;
        }
    }
    //if not found return the default
    return defaultTextureID;
}
