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

void BaseShader::baseInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath)
{
    //load our basic shader
    ID3DBlob* VS, * PS, * errorBlob;
    HRESULT hr = D3DCompileFromFile(vsFilePath, 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VS, &errorBlob);
    //HRESULT hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VS, &errorBlob);
    checkForShaderCompileError(hr, VS, errorBlob);
    hr = D3DCompileFromFile(psFilePath, 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PS, &errorBlob);
    //hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PS, &errorBlob);
    checkForShaderCompileError(hr, PS, errorBlob);
    //set into the shader objects
    ThrowIfFailed(pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS));
    ThrowIfFailed(pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS));
    //set as current shaders
    pDeviceContext->VSSetShader(m_pVS, 0, 0);
    pDeviceContext->PSSetShader(m_pPS, 0, 0);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    ThrowIfFailed(pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout));
    pDeviceContext->IASetInputLayout(m_pLayout);
}

void BaseShader::checkForShaderCompileError(HRESULT hr, ID3DBlob* shaderBlob, ID3DBlob* errorBlob)
{
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }

        if (shaderBlob)
            shaderBlob->Release();
    }
    ThrowIfFailed(hr);
}