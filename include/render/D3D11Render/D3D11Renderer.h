#ifndef D3D11RENDERER_H_
#define D3D11RENDERER_H_

#include "stdafx.h"
#include "render/Renderer.h"
#include "render/Camera.h"
#include "render/D3D11Render/BaseShader.h"

#include "render/D3D11Render/BasicTextureShader.h"
#include "render/D3D11Render/D3D11TextureManager.h"

#include "ecs/World.h"
#include "ecs/System.h"
#include "ecs/Entity.h"


class D3D11Renderer : public Renderer, public ECS::System
{
private:
    //this is not at the right level currently, the gamestate should own this. Once it is created.
    //also a strat needs to be formulated for if we are using DRXMath or glm; glm works too currently
    D3D11Camera* m_pCamera;
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pDeviceContext;
    ID3D11RenderTargetView* m_pRenderTarget; //typically called the backbuffer
    ID3D11DepthStencilView* m_pDepthBuffer;
    ID3D11Buffer* m_pVBuffer;//will be part of render nodes or mesh manager
    ID3D11Buffer* m_pIBuffer;//will be part of render nodes or mesh manager
    IDXGISwapChain* m_pSwapChain;

    BasicTextureShader* m_pShader;

    //managers/handlers that will need to be abstracted outside of the renderer in use
    D3D11TextureManager m_textureManager;

    const float m_clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

    void initializePipeline(void);
    void initializeDepthAndStencilBuffer(void);
    void updateEntity(float fDt, ECS::Entity_ID pEntity);

    //state variables
    Texture_ID m_currTextID = maxTextureID;
public:
    D3D11Renderer(ECS::World* world);
    ~D3D11Renderer(void) {}
    bool initialize(void);
    void update(float dT);
    void render(void);
    bool shutdown(void);
    inline D3D11Camera* getCamera(void) { return m_pCamera; }
    //inline Camera* getCamera(void) { return m_pCamera; }
};

#endif //D3D11RENDERER_H_
