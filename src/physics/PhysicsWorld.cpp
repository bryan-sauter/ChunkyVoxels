#include "physics/PhysicsWorld.h"

#include "ecs/World.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/SimpleColliderComponent.h"
#include "helpers/HResultHelpers.h" //SAFE_DELETE

PhysicsWorld::PhysicsWorld(ECS::World* world) : ECS::System(world)
{
    ///collision configuration contains default setup for memory, collision setup
    m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
    //m_collisionConfiguration->setConvexConvexMultipointIterations();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);

    m_pBroadphase = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
    m_pSolver = sol;

    m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

    m_pDynamicsWorld->setGravity(btVector3(0, -10, 0));

    ///create a few basic rigid bodies
    btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    m_aCollisionShapes.push_back(groundShape);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -55, 0));
    {
        btScalar mass(0.);
        createRigidBody(mass, groundTransform, groundShape, btVector4(0, 0, 1, 1));
    }

    //create a few dynamic rigidbodies
// Re-using the same collision is better for memory usage and performance

    colShape = createBoxShape(btVector3(0.5, 0.5, 0.5));

    //btCollisionShape* colShape = new btSphereShape(btScalar(1.));
    m_aCollisionShapes.push_back(colShape);

    addRegisteredComponents(ECS::eComponentType::ECS_COMP_TRANSFORM);
    addRegisteredComponents(ECS::eComponentType::ECS_COMP_SIMPLECOLLIDER);
}

void PhysicsWorld::tick(double fDt)
{
    if (m_pDynamicsWorld)
    {
        m_pDynamicsWorld->stepSimulation((float)fDt);
    }
}

void PhysicsWorld::updateEntity(double fDt, ECS::Entity_ID pEntity)
{
    ECS::SimpleColliderComponent* cComp = ECS::System::m_world->getComponentStorage<ECS::SimpleColliderComponent>()->get(pEntity);
    btTransform transform = cComp->getBody()->getWorldTransform();
    ECS::TransformComponent* comp =
        ECS::System::m_world->getComponentStorage<ECS::TransformComponent>()->get(pEntity);
    comp->setPhysicsTransform(transform.getOrigin(), transform.getRotation());
}

void PhysicsWorld::shutdown(void)
{
    if (m_pDynamicsWorld)
    {
        int i;
        for (i = m_pDynamicsWorld->getNumConstraints() - 1; i >= 0; i--)
        {
            m_pDynamicsWorld->removeConstraint(m_pDynamicsWorld->getConstraint(i));
        }
        for (i = m_pDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = m_pDynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }
            m_pDynamicsWorld->removeCollisionObject(obj);
            SAFE_DELETE(obj);
        }
    }
    //delete collision shapes
    for (int j = 0; j < m_aCollisionShapes.size(); j++)
    {
        btCollisionShape* shape = m_aCollisionShapes[j];
        SAFE_DELETE(shape);
    }
    m_aCollisionShapes.clear();
    //clean up dynamic memory
    SAFE_DELETE(m_pDynamicsWorld);
    SAFE_DELETE(m_pSolver);
    SAFE_DELETE(m_pBroadphase);
    SAFE_DELETE(m_pDispatcher);
    SAFE_DELETE(m_pCollisionConfiguration);
}

btBoxShape* PhysicsWorld::createBoxShape(const btVector3& halfExtents)
{
    btBoxShape* box = new btBoxShape(halfExtents);
    return box;
}

btRigidBody* PhysicsWorld::createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color)
{
    btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic && shape)
        shape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

    btRigidBody* body = new btRigidBody(cInfo);

    body->setUserIndex(-1);
    m_pDynamicsWorld->addRigidBody(body);
    body->getWorldTransform().getOrigin();
    return body;
}