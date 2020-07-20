#ifndef D3D11RENDERER_H_
#define D3D11RENDERER_H_

#include "stdafx.h"
#include "render/Renderer.h"

class D3D11Renderer : public Renderer
{
private:
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pDeviceContext;
    ID3D11RenderTargetView* m_pRenderTarget; //typically called the backbuffer
    ID3D11VertexShader* m_pVS;
    ID3D11PixelShader* m_pPS;
    ID3D11Buffer* m_pVBuffer;
    ID3D11Buffer* m_pIBuffer;
    ID3D11Buffer* m_pCBuffer;
    ID3D11InputLayout* m_pLayout;
    IDXGISwapChain* m_pSwapChain;
    struct VS_CONSTANT_BUFFER {
        DirectX::XMFLOAT4X4 mWorldViewProj;
    }m_sConstantBuffer;

    const float m_clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

    void initializePipeline(void);

    void checkForShaderCompileError(HRESULT hr, ID3DBlob* shaderBlob, ID3DBlob* errorBlob);

public:
    bool initialize(void);
    void update(float dT);
    void render(void);
    bool shutdown(void);
};

#endif //D3D11RENDERER_H_
