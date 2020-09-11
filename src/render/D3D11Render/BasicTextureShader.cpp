#include "render/D3D11Render/BasicTextureShader.h"
#include "helpers/HResultHelpers.h"

#include <DDSTextureLoader.h>

void BasicTextureShader::initShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
    //create the constant buffer description
    D3D11_BUFFER_DESC cbd;
    cbd.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;
    //define the initial data of the buffer
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = &this->m_sConstantBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    //hook the buffer up
    ThrowIfFailed(pDevice->CreateBuffer(&cbd, &InitData, &m_pCBuffer));
    pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCBuffer);
}

void BasicTextureShader::updateShader(ID3D11DeviceContext* pDeviceContext, DirectX::XMMATRIX mWVP)
{
    this->m_sConstantBuffer.mWorldViewProj = mWVP;
    ThrowIfFailed(pDeviceContext->Map(m_pCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_sMappedResource));
    memcpy(m_sMappedResource.pData, &m_sConstantBuffer, sizeof(m_sConstantBuffer));
    pDeviceContext->Unmap(m_pCBuffer, 0);
}

void BasicTextureShader::updateShader(ID3D11DeviceContext* pDeviceContext, glm::mat4 mWVP)
{
    this->m_sConstantBuffer.mWorldViewProj = DirectX::XMMATRIX(&mWVP[0][0]);
    ThrowIfFailed(pDeviceContext->Map(m_pCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_sMappedResource));
    memcpy(m_sMappedResource.pData, &m_sConstantBuffer, sizeof(m_sConstantBuffer));
    pDeviceContext->Unmap(m_pCBuffer, 0);
}

BasicTextureShader::BasicTextureShader(void) : m_pCBuffer(nullptr), m_sConstantBuffer(DirectX::XMMatrixIdentity()), BaseShader()
{
    ZeroMemory(&m_sMappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
}

BasicTextureShader::~BasicTextureShader(void)
{
    SAFE_RELEASE(m_pCBuffer);
}

void BasicTextureShader::initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath)
{
    ID3DBlob* VS(nullptr), * PS(nullptr);
    BaseShader::baseInitialize(pDevice, pDeviceContext, vsFilePath, psFilePath, &VS, &PS);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    ThrowIfFailed(pDevice->CreateInputLayout(ied, ARRAYSIZE(ied), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout));
    pDeviceContext->IASetInputLayout(m_pLayout);

    initShader(pDevice, pDeviceContext);
}

void BasicTextureShader::loadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const wchar_t* texFilePath)
{
    ThrowIfFailed(DirectX::CreateDDSTextureFromFile(pDevice, texFilePath, &m_pTexture, &m_pResourceView));

    pDeviceContext->GenerateMips(m_pResourceView);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    ThrowIfFailed(pDevice->CreateSamplerState(&sampDesc, &m_pSampleState));

    pDeviceContext->PSSetShaderResources(0, 1, &m_pResourceView);
    pDeviceContext->PSSetSamplers(0, 1, &m_pSampleState);
}
