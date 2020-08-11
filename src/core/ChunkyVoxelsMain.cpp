#include "stdafx.h"
#include "core/ChunkyVoxelsMain.h"
#include "render/Camera.h"
#include "render/D3D11Render/D3D11Renderer.h"
#include "helpers/HResultHelpers.h"

#include "ecs/World.h"
#include "ecs/System.h"

ChunkyVoxelsMain::ChunkyVoxelsMain() : m_hWnd(NULL), m_hInstance(NULL), m_pRenderer(nullptr)
{
}

void ChunkyVoxelsMain::initialize(HWND hWnd, HINSTANCE hInstance)
{
    this->m_hWnd = hWnd;
    this->m_hInstance = hInstance;

    ECS::World* world = new ECS::World();
    m_pRenderer = new D3D11Renderer(world);
    m_pRenderer->initialize();
    for (int i = 0; i < 100; ++i)
    {
        m_vRenderNodes.push_back(*(new RenderNode(1.0f * i, 0.0f, 0.0f)));
        m_pRenderer->addRenderNode(&(m_vRenderNodes[i]));
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
    SAFE_SHUTDOWN(m_pRenderer);
}
