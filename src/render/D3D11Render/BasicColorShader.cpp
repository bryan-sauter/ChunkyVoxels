#include "render/D3D11Render/BasicColorShader.h"

#include "helpers/HResultHelpers.h"

void BasicColorShader::initShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
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

void BasicColorShader::updateShader(ID3D11DeviceContext* pDeviceContext, DirectX::XMMATRIX mWVP)
{
    this->m_sConstantBuffer.mWorldViewProj = mWVP;
    ThrowIfFailed(pDeviceContext->Map(m_pCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_sMappedResource));
    memcpy(m_sMappedResource.pData, &m_sConstantBuffer, sizeof(m_sConstantBuffer));
    pDeviceContext->Unmap(m_pCBuffer, 0);
}

void BasicColorShader::updateShader(ID3D11DeviceContext* pDeviceContext, glm::mat4 mWVP)
{
    this->m_sConstantBuffer.mWorldViewProj = DirectX::XMMATRIX(&mWVP[0][0]);
    ThrowIfFailed(pDeviceContext->Map(m_pCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_sMappedResource));
    memcpy(m_sMappedResource.pData, &m_sConstantBuffer, sizeof(m_sConstantBuffer));
    pDeviceContext->Unmap(m_pCBuffer, 0);
}

BasicColorShader::BasicColorShader(void) : m_pCBuffer(nullptr), m_sConstantBuffer(DirectX::XMMatrixIdentity()), BaseShader()
{
    ZeroMemory(&m_sMappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
}

BasicColorShader::~BasicColorShader(void)
{
    SAFE_RELEASE(m_pCBuffer);
}

void BasicColorShader::initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath)
{
    ID3DBlob* VS(nullptr), * PS(nullptr);
    BaseShader::baseInitialize(pDevice, pDeviceContext, vsFilePath, psFilePath, &VS, &PS);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    ThrowIfFailed(pDevice->CreateInputLayout(ied, ARRAYSIZE(ied), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout));
    pDeviceContext->IASetInputLayout(m_pLayout);

    initShader(pDevice, pDeviceContext);
}
