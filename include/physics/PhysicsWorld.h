#ifndef PHYSICSWORLD_H_
#define PHYSICSWORLD_H_

#include "ecs/System.h"

#include "bullet/btBulletDynamicsCommon.h"

class PhysicsWorld : public ECS::System
{
private:
    btBroadphaseInterface* m_pBroadphase;
    btCollisionDispatcher* m_pDispatcher;
    btConstraintSolver* m_pSolver;
    btDefaultCollisionConfiguration* m_pCollisionConfiguration;
    btDiscreteDynamicsWorld* m_pDynamicsWorld;
    //might be temporary
    btAlignedObjectArray<btCollisionShape*> m_aCollisionShapes;

    void updateEntity(double fDt, ECS::Entity_ID pEntity);

    //helpers
    btBoxShape* createBoxShape(const btVector3& halfExtents);
    

public:
    PhysicsWorld(ECS::World* world);
    ~PhysicsWorld(void) {}
    void tick(double fDt);
    void shutdown(void);

    btBoxShape* colShape;

    btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color = btVector4(1, 0, 0, 1));
};




#endif //PHYSICSWORLD_H_