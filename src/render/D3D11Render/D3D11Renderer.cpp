#include "render/D3D11Render/D3D11Renderer.h"

#include "helpers/HResultHelpers.h"
#include "helpers/Globals.h"
#include "core/CGame.h"
#include "render/D3D11Render/D3D11Declares.h"

bool D3D11Renderer::initialize(void)
{
    //declare the swap chain description struct
    DXGI_SWAP_CHAIN_DESC swapChainDESC;
    //make sure the struct is empty
    ZeroMemory(&swapChainDESC, sizeof(DXGI_SWAP_CHAIN_DESC));
    //set the values in the swap chain struct
    swapChainDESC.BufferCount = 1;                                      // one back buffer
    swapChainDESC.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // use 32-bit color
    swapChainDESC.BufferDesc.Width = Globals::getInstance().getWindowWidth();
    swapChainDESC.BufferDesc.Height = Globals::getInstance().getWindowHeight();
    swapChainDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;        // how swap chain is to be used
    swapChainDESC.OutputWindow = CGame::getInstance().getHWND();        // the window to be used
    swapChainDESC.SampleDesc.Count = 4;                                 // how many multisamples
    swapChainDESC.Windowed = !Globals::getInstance().getFullScreen();   // windowed/full-screen mode
    swapChainDESC.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;       // allow full-screen switching
    // create a device, device context and swap chain using the information in the swapChainDESC struct
    ThrowIfFailed(D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &swapChainDESC,
        &m_pSwapChain,
        &m_pDevice,
        NULL,
        &m_pDeviceContext));
    //get the backbuffer address
    ID3D11Texture2D* pBackBuffer;
    ThrowIfFailed(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));
    //use back buffer to create render target
    ThrowIfFailed(m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTarget));
    SAFE_RELEASE(pBackBuffer);
    //set the render target as the back buffer
    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTarget, NULL);
    //setup the viewport
    D3D11_VIEWPORT viewPort;
    //zero the struct
    ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
    //set values in struct
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = Globals::getInstance().getWindowWidth();
    viewPort.Height = Globals::getInstance().getWindowHeight();
    //set viewport
    m_pDeviceContext->RSSetViewports(1, &viewPort);

    this->m_Camera.buildPerspective(glm::pi<float>() / 3.0f, 0.1f, 5000.0f);
    this->m_Camera.setViewPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 mvp = this->m_Camera.getProjectionMatrix() * this->m_Camera.getViewMatrix();
    this->m_sConstantBuffer.mWorldViewProj = DirectX::XMFLOAT4X4(&mvp[0][0]);

    initializePipeline();

    return true;
}

void D3D11Renderer::initializePipeline(void)
{
    //load our basic shader
    ID3DBlob* VS, * PS, * errorBlob;
    HRESULT hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG| D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VS, &errorBlob);
    checkForShaderCompileError(hr, VS, errorBlob);
    hr = D3DCompileFromFile(L"./resource/render/D3D11Renderer/triangle.shader", 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG| D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PS, &errorBlob);
    checkForShaderCompileError(hr, PS, errorBlob);
    //set into the shader objects
    ThrowIfFailed(m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS));
    ThrowIfFailed(m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS));
    //set as current shaders
    m_pDeviceContext->VSSetShader(m_pVS, 0, 0);
    m_pDeviceContext->PSSetShader(m_pPS, 0, 0);

    

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * (UINT)(*(&SimpleIndexedCube + 1)-SimpleIndexedCube);             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    ThrowIfFailed(m_pDevice->CreateBuffer(&bd, NULL, &m_pVBuffer));       // create the buffer

        // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    ThrowIfFailed(m_pDeviceContext->Map(m_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms));    // map the buffer
    memcpy(ms.pData, SimpleIndexedCube, sizeof(SimpleIndexedCube));                 // copy the data
    m_pDeviceContext->Unmap(m_pVBuffer, NULL);                                      // unmap the buffer

        // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    ThrowIfFailed(m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout));
    m_pDeviceContext->IASetInputLayout(m_pLayout);

    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = sizeof(unsigned int) * 36;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    //define the resource data
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = buildCubeIndex();
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    // Create the buffer with the device.
    ThrowIfFailed(m_pDevice->CreateBuffer(&ibd, &InitData, &m_pIBuffer));

    // Set the buffer.
    m_pDeviceContext->IASetIndexBuffer(m_pIBuffer, DXGI_FORMAT_R32_UINT, 0);

    D3D11_BUFFER_DESC cbd;
    cbd.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;

    InitData.pSysMem = &this->m_sConstantBuffer;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    ThrowIfFailed(m_pDevice->CreateBuffer(&cbd, &InitData, &m_pCBuffer));
    m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCBuffer);
}

void D3D11Renderer::checkForShaderCompileError(HRESULT hr, ID3DBlob* shaderBlob, ID3DBlob* errorBlob)
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

void D3D11Renderer::update(float dT)
{
}

void D3D11Renderer::render(void)
{
    //clear the back buffer to a color
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTarget, m_clearColor);

    // select which vertex buffer to display
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVBuffer, &stride, &offset);

    // select which primtive type we are using
    m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // draw the vertex buffer to the back buffer
    m_pDeviceContext->DrawIndexed(36, 0, 0);

    m_pSwapChain->Present(0, 0);
}

bool D3D11Renderer::shutdown(void)
{
    //switch to windowed to shutdown
    m_pSwapChain->SetFullscreenState(FALSE, NULL);

    SAFE_RELEASE(m_pVS);
    SAFE_RELEASE(m_pPS);
    SAFE_RELEASE(m_pSwapChain);
    SAFE_RELEASE(m_pRenderTarget);
    SAFE_RELEASE(m_pDevice);
    SAFE_RELEASE(m_pDeviceContext);
    return true;
}
