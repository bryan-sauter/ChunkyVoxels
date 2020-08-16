#include "render/D3D11Render/D3D11Renderer.h"

#include "helpers/HResultHelpers.h"
#include "helpers/Globals.h"
#include "core/ChunkyVoxelsMain.h"
#include "ecs/World.h"
#include "render/D3D11Render/D3D11Declares.h"

#include "render/D3D11Render/BasicColorShader.h"
#include "render/RenderNode.h"

D3D11Renderer::D3D11Renderer(ECS::World* world) : ECS::System(world)
{
    m_pCamera = nullptr;
    m_pDevice = nullptr;
    m_pDeviceContext = nullptr;
    m_pRenderTarget = nullptr;
    m_pDepthBuffer = nullptr;
    m_pVBuffer = nullptr;
    m_pIBuffer = nullptr;
    m_pSwapChain = nullptr;

    m_pShader = nullptr;
}

bool D3D11Renderer::initialize(void)
{
    m_pCamera = new D3D11Camera();
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
    swapChainDESC.OutputWindow = ChunkyVoxelsMain::getInstance().getHWND();        // the window to be used
    swapChainDESC.SampleDesc.Count = 1;                                 // how many multisamples
    swapChainDESC.SampleDesc.Quality = 0;
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
    viewPort.MinDepth = 0;
    viewPort.MaxDepth = 1.0f;
    viewPort.Width = Globals::getInstance().getWindowWidth();
    viewPort.Height = Globals::getInstance().getWindowHeight();
    //set viewport
    m_pDeviceContext->RSSetViewports(1, &viewPort);


    this->m_pCamera->buildPerspective(glm::pi<float>()/4.0f, 0.1f, 5000.0f);
    this->m_pCamera->setViewPosition(10.0f, 0.0f, -50.0f);

    m_pShader = new BasicColorShader();
    m_pShader->initialize(m_pDevice, m_pDeviceContext,
                                    L"./resource/render/D3D11Renderer/triangle.shader",
                                    L"./resource/render/D3D11Renderer/triangle.shader");

    initializePipeline();
    initializeDepthAndStencilBuffer();
 
    return true;
}

void D3D11Renderer::initializePipeline(void)
{
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

    SAFE_DELETE(InitData.pSysMem);
}

void D3D11Renderer::initializeDepthAndStencilBuffer(void)
{
    D3D11_TEXTURE2D_DESC depthTextureDesc;
    ZeroMemory(&depthTextureDesc, sizeof(depthTextureDesc));
    depthTextureDesc.Width = Globals::getInstance().getWindowWidth();
    depthTextureDesc.Height = Globals::getInstance().getWindowHeight();
    depthTextureDesc.MipLevels = 1;
    depthTextureDesc.ArraySize = 1;
    depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthTextureDesc.SampleDesc.Count = 1;
    depthTextureDesc.SampleDesc.Quality = 0;
    depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthTextureDesc.CPUAccessFlags = 0;
    depthTextureDesc.MiscFlags = 0;

    D3D11_DEPTH_STENCIL_DESC dsDesc;

    // Depth test parameters
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    // Stencil test parameters
    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = 0xFF;
    dsDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing
    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create depth stencil state
    ID3D11DepthStencilState* pDSState;
    ThrowIfFailed(m_pDevice->CreateDepthStencilState(&dsDesc, &pDSState));
    m_pDeviceContext->OMSetDepthStencilState(pDSState, 1);

    ID3D11Texture2D* DepthStencilTexture;
    ThrowIfFailed(m_pDevice->CreateTexture2D(&depthTextureDesc, NULL, &DepthStencilTexture));

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    ZeroMemory(&dsvDesc, sizeof(dsvDesc));
    dsvDesc.Format = depthTextureDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

    ThrowIfFailed(m_pDevice->CreateDepthStencilView(DepthStencilTexture, &dsvDesc, &m_pDepthBuffer));
    DepthStencilTexture->Release();

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTarget, m_pDepthBuffer);
}

void D3D11Renderer::updateEntity(float fDt, ECS::Entity_ID pEntity)
{
}

void D3D11Renderer::update(float dT)
{
    m_pShader->updateShader(m_pDeviceContext, XMMatrixTranspose(m_pCamera->getViewMatrix() * m_pCamera->getProjectionMatrix()));
//    m_pShader->updateShader(m_pDeviceContext, glm::transpose(m_pCamera->getProjectionMatrix() * m_pCamera->getViewMatrix()));
}

void D3D11Renderer::render(void)
{
    //clear the back buffer to a color
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTarget, m_clearColor);
    m_pDeviceContext->ClearDepthStencilView(m_pDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // select which vertex buffer to display
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVBuffer, &stride, &offset);
    m_pDeviceContext->IASetIndexBuffer(m_pIBuffer, DXGI_FORMAT_R32_UINT, 0);

    // select which primtive type we are using
    m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    XMMATRIX matVP = m_pCamera->getViewMatrix() * m_pCamera->getProjectionMatrix();
    glm::vec3 vPosition;
    for (vector<RenderNode*>::iterator it = m_RenderSet.getBeginIterator(); it != m_RenderSet.getEndIterator(); ++it) {
        // draw the vertex buffer to the back buffer
        vPosition = (*it)->getPosition();
        XMMATRIX translation = XMMatrixTranslation(vPosition.x, vPosition.y, vPosition.z);
        m_pShader->updateShader(m_pDeviceContext, XMMatrixTranspose(translation * matVP));
        m_pDeviceContext->DrawIndexed(36, 0, 0);
    }

    m_pSwapChain->Present(0, 0);
}

bool D3D11Renderer::shutdown(void)
{
    //switch to windowed to shutdown
    m_pSwapChain->SetFullscreenState(FALSE, NULL);

    SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pShader);
    //needs to be removed but just for ease of testing, doing the clean up here for now
    SAFE_DELETE(this->m_world);

    SAFE_RELEASE(m_pSwapChain);
    SAFE_RELEASE(m_pRenderTarget);
    SAFE_RELEASE(m_pDepthBuffer);
    SAFE_RELEASE(m_pDevice);
    SAFE_RELEASE(m_pDeviceContext);
    return true;
}
