#include "stdafx.h"
#include "core/CGame.h"
#include "render/D3D11Render/D3D11Renderer.h"

CGame::CGame() : m_hWnd(NULL), m_hInstance(NULL), m_pRenderer(nullptr)
{
}

void CGame::initialize(HWND hWnd, HINSTANCE hInstance)
{
    this->m_hWnd = hWnd;
    this->m_hInstance = hInstance;

    m_pRenderer = new D3D11Renderer();
    m_pRenderer->initialize();
}

void CGame::tick(float fDt)
{
    if (GetAsyncKeyState('A'))
    {
        m_pRenderer->getCamera()->viewRotateLocalY(-XMConvertToRadians(5.0f) * fDt * 5.0f);
    }
    if (GetAsyncKeyState('D'))
    {
        m_pRenderer->getCamera()->viewRotateLocalY(XMConvertToRadians(5.0f) * fDt * 5.0f);
    }
    if (GetAsyncKeyState('W'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalZ(fDt * 5.0f);
    }
    if (GetAsyncKeyState('S'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalZ(-fDt * 5.0f);
    }
    if (GetAsyncKeyState('R'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalY(fDt * 5.0f);
    }
    if (GetAsyncKeyState('F'))
    {
        m_pRenderer->getCamera()->viewTranslateLocalY(-fDt * 5.0f);
    }
    if (GetAsyncKeyState(VK_ESCAPE))
        PostQuitMessage(0);
    if (m_pRenderer) {
        m_pRenderer->render();
    }
}

void CGame::shutdown(void)
{
    if (m_pRenderer) {
        m_pRenderer->shutdown();
    }
}
