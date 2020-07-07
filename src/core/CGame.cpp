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

void CGame::tick(void)
{
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
