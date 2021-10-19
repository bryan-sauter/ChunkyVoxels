#ifndef CGAME_H_
#define CGAME_H_

#include "stdafx.h"
#include "render/Renderer.h"
#include "physics/PhysicsWorld.h"

//temp
#include <vector>
#include "render/RenderNode.h"

#include "ecs/World.h"
#include "ecs/System.h"

class ChunkyVoxelsMain
{

private:
    HWND m_hWnd;
    HINSTANCE m_hInstance;
    Renderer* m_pRenderer;
    PhysicsWorld* m_pPhysicsContainer;
    ECS::System* m_pPhysicsWorld;
    ECS::System* m_pRenderSystem;
    ECS::World* m_pWorld;

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