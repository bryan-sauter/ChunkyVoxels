#ifndef CGAME_H_
#define CGAME_H_

#include "stdafx.h"
#include "render/Renderer.h"

//temp
#include <vector>
#include "render/RenderNode.h"

class ChunkyVoxelsMain
{

private:
    HWND m_hWnd;
    HINSTANCE m_hInstance;
    Renderer* m_pRenderer;

    vector<RenderNode> m_vRenderNodes;

    ChunkyVoxelsMain();

public:
    static ChunkyVoxelsMain& getInstance()
    {
        static ChunkyVoxelsMain instance;
        return instance;
    }
    ChunkyVoxelsMain(ChunkyVoxelsMain const&) = delete;
    void operator=(ChunkyVoxelsMain const&) = delete;

    void initialize(HWND hWnd, HINSTANCE hInstance);
    void tick(float fDt);
    void shutdown(void);


    HWND getHWND(void) { return m_hWnd; }
};

#endif //CGAME_H_