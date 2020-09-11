#include "render/D3D11Render/BaseShader.h"

#include "helpers/HResultHelpers.h"

BaseShader::BaseShader(void):m_pVS(nullptr),m_pPS(nullptr),m_pLayout(nullptr)
{
}

BaseShader::~BaseShader(void)
{
    release();
}

void BaseShader::release(void)
{
    SAFE_RELEASE(m_pVS);
    SAFE_RELEASE(m_pPS);
    SAFE_RELEASE(m_pLayout);
}

void BaseShader::baseInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath, ID3DBlob** VS, ID3DBlob** PS)
{
    //load our basic shader
    ID3DBlob* errorBlob;
#if CV_DEBUG
    HRESULT hr = D3DCompileFromFile(vsFilePath, 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, VS, &errorBlob);
#else
    HRESULT hr = D3DCompileFromFile(vsFilePath, 0, 0, "VShader", "vs_4_0", 0, 0, &VS, &errorBlob);
#endif
    //HRESULT hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VS, &errorBlob);
    checkForShaderCompileError(hr, *VS, errorBlob);
#if CV_DEBUG
    hr = D3DCompileFromFile(psFilePath, 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, PS, &errorBlob);
#else
    hr = D3DCompileFromFile(psFilePath, 0, 0, "PShader", "ps_4_0", 0, 0, &PS, &errorBlob);
#endif
    //hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PS, &errorBlob);
    checkForShaderCompileError(hr, *PS, errorBlob);
    //set into the shader objects
    ThrowIfFailed(pDevice->CreateVertexShader((*VS)->GetBufferPointer(), (*VS)->GetBufferSize(), NULL, &m_pVS));
    ThrowIfFailed(pDevice->CreatePixelShader((*PS)->GetBufferPointer(), (*PS)->GetBufferSize(), NULL, &m_pPS));
    //set as current shaders
    pDeviceContext->VSSetShader(m_pVS, 0, 0);
    pDeviceContext->PSSetShader(m_pPS, 0, 0);
}

void BaseShader::checkForShaderCompileError(HRESULT hr, ID3DBlob* shaderBlob, ID3DBlob* errorBlob)
{
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            SAFE_RELEASE(errorBlob);
        }

        if (shaderBlob)
            SAFE_RELEASE(shaderBlob);
    }
    ThrowIfFailed(hr);
}