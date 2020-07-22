#ifndef CGAME_H_
#define CGAME_H_

#include "stdafx.h"
#include "render/Renderer.h"

class CGame
{

private:
    HWND m_hWnd;
    HINSTANCE m_hInstance;
    Renderer* m_pRenderer;

    CGame();

public:
    static CGame& getInstance()
    {
        static CGame instance;
        return instance;
    }
    CGame(CGame const&) = delete;
    void operator=(CGame const&) = delete;

    void initialize(HWND hWnd, HINSTANCE hInstance);
    void tick(float fDt);
    void shutdown(void);


    HWND getHWND(void) { return m_hWnd; }
};

#endif //CGAME_H_