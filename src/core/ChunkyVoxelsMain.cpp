#include "stdafx.h"
#include "core/ChunkyVoxelsMain.h"
#include "render/Camera.h"
#include "render/D3D11Render/D3D11Renderer.h"
#include "helpers/HResultHelpers.h"

#include "ecs/World.h"
#include "ecs/System.h"

#include "ecs/components/SimpleColliderComponent.h"
#include "ecs/Components/TransformComponent.h"
#include "ecs/Components/RenderComponent.h"

#include "physics/PhysicsWorld.h"

ChunkyVoxelsMain::ChunkyVoxelsMain() : m_hWnd(NULL), m_hInstance(NULL), m_pRenderer(nullptr)
{
}

void ChunkyVoxelsMain::initialize(HWND hWnd, HINSTANCE hInstance)
{
    this->m_hWnd = hWnd;
    this->m_hInstance = hInstance;

    m_pWorld = new ECS::World();
    //crude implementation to avoid slashing
    //the real cost is the allocation of components below
    //the world should manage pools for the components
    /*m_pWorld->preallocateStorage<ECS::TransformComponent>(125);
    m_pWorld->preallocateStorage<ECS::RenderComponent>(125);
    m_pWorld->preallocateStorage<ECS::SimpleColliderComponent>(125);*/

    m_pPhysicsWorld = new PhysicsWorld(m_pWorld);
    m_pPhysicsContainer = dynamic_cast<PhysicsWorld*>(m_pPhysicsWorld);
    m_pWorld->addSystem(m_pPhysicsWorld);

    m_pRenderSystem = new D3D11Renderer(m_pWorld);
    m_pRenderer = dynamic_cast<D3D11Renderer*>(m_pRenderSystem);
    m_pRenderer->initialize();
    
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                ECS::Entity_ID entity = m_pWorld->createEntity();
                /// Create Dynamic Objects
                btTransform startTransform;
                startTransform.setIdentity();

                btScalar mass(1.f);

                //rigidbody is dynamic if and only if mass is non zero, otherwise static
                bool isDynamic = (mass != 0.f);

                btVector3 localInertia(0, 0, 0);
                if (isDynamic)
                    m_pPhysicsContainer->colShape->calculateLocalInertia(mass, localInertia);

                startTransform.setOrigin(btVector3(
                    btScalar(4.0 + 1.0 * i),
                    btScalar(75.0 + 1.0 * k),
                    btScalar(-2.0 + -1.0 * j)));

                ECS::SimpleColliderComponent* cComp = new ECS::SimpleColliderComponent(entity,
                    m_pPhysicsContainer->createRigidBody(mass, startTransform, m_pPhysicsContainer->colShape));
                m_pWorld->addComponent<ECS::SimpleColliderComponent>(entity, cComp);
                
                //contiguous memory will increase performance here
                //the plan in a later release is to use pools instead, everyone loves swimming right?
                ECS::TransformComponent* tComp = new ECS::TransformComponent(entity, 1.0f * i, 2.0f + 1.0f * k, 1.0f * j);
                m_pWorld->addComponent<ECS::TransformComponent>(entity, tComp);

                ECS::RenderComponent* rComp = new ECS::RenderComponent(entity, defaultTextureID, tComp);
                m_pWorld->addComponent<ECS::RenderComponent>(entity, rComp);

                m_pWorld->registerEntity(entity);
            }
        }
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

    m_pPhysicsContainer->tick(fDt);

    m_pWorld->updateEntities(fDt);

    if (m_pRenderer) {
        m_pRenderer->update(fDt);
        m_pRenderer->render();
    }
}

void ChunkyVoxelsMain::shutdown(void)
{
    m_pPhysicsContainer->shutdown();
    m_pRenderer->shutdown();
    SAFE_DELETE(m_pRenderSystem);
    SAFE_DELETE(m_pWorld);
}
