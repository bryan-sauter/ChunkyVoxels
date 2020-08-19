#include "stdafx.h"
#include "core/ChunkyVoxelsMain.h"
#include "render/Camera.h"
#include "render/D3D11Render/D3D11Renderer.h"
#include "helpers/HResultHelpers.h"

#include "ecs/World.h"
#include "ecs/System.h"

#include "ecs/Components/TransformComponent.h"

ChunkyVoxelsMain::ChunkyVoxelsMain() : m_hWnd(NULL), m_hInstance(NULL), m_pRenderer(nullptr)
{
}

void ChunkyVoxelsMain::initialize(HWND hWnd, HINSTANCE hInstance)
{
    this->m_hWnd = hWnd;
    this->m_hInstance = hInstance;

    m_pWorld = new ECS::World();

    m_pRenderSystem = new D3D11Renderer(m_pWorld);
    m_pRenderer = dynamic_cast<D3D11Renderer*>(m_pRenderSystem);
    m_pRenderer->initialize();
    m_pWorld->addSystem(m_pRenderSystem);
    m_pWorld->createComponentStorage<ECS::TransformComponent>();

    for (int i = 0; i < 100; ++i)
        for( unsigned int j = 0; j < 100; ++j)
    {
        ECS::Entity_ID entity = m_pWorld->createEntity();
        ECS::TransformComponent* tComp = new ECS::TransformComponent(1.0f * i, 0.0f, 1.0f * j);
        m_pWorld->addComponent<ECS::TransformComponent>(entity, tComp);
        m_pWorld->registerEntity(entity);
    }
}

void ChunkyVoxelsMain::tick(float fDt)
{
    if (GetAsyncKeyState('A'))
    {
        m_pRenderer->getCamera()->viewRotateLocalY(-XMConvertToRadians(7.0f) * fDt * 5.0f);
    }
    if (GetAsyncKeyState('D'))
    {
        m_pRenderer->getCamera()->viewRotateLocalY(XMConvertToRadians(7.0f) * fDt * 5.0f);
    }
    if (GetAsyncKeyState('W'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalZ(FORWARD_SPEED * fDt * 5.0f);
    }
    if (GetAsyncKeyState('S'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalZ(FORWARD_SPEED * -fDt * 5.0f);
    }
    if (GetAsyncKeyState('R'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalY(FORWARD_SPEED * fDt * 5.0f);
    }
    if (GetAsyncKeyState('F'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalY(FORWARD_SPEED * -fDt * 5.0f);
    }
    if (GetAsyncKeyState(VK_ESCAPE))
        PostQuitMessage(0);
    if (m_pRenderer) {
        m_pRenderer->update(fDt);
        m_pRenderer->render();
    }
}

void ChunkyVoxelsMain::shutdown(void)
{
    for (unsigned int i = 0; i < m_vRenderNodes.size(); ++i)
    {
        delete m_vRenderNodes[i];
    }
    SAFE_SHUTDOWN(m_pRenderer);
    SAFE_DELETE(m_pWorld);
}
