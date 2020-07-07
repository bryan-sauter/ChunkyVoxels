#include "render/D3D11Render/BaseShader.h"

BaseShader::BaseShader()
{
    m_pVertexShader = nullptr;
    m_pPixelShader = nullptr;
    m_pInputLayout = nullptr;
    m_pSampleState = nullptr;
    m_pMatrixBuffer = nullptr;
    m_pLightBuffer = nullptr;
}

bool BaseShader::Initialize(ID3D11Device* pDevice, WCHAR* vsFilePath, WCHAR* psFilePath)
{

    return false;
}
