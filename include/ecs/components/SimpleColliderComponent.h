#ifndef SIMPLECOLLIDERCOMPONENT_H_
#define SIMPLECOLLIDERCOMPONENT_H_

#include "stdafx.h"
#include "ecs/Component.h"
#include "ecs/ECSTypes.h"
#include "ecs/Entity.h"

#include "bullet/btBulletDynamicsCommon.h"

namespace ECS
{
    //simple colliders are AABB based on an entities transform
    class SimpleColliderComponent : public Component
    {
    private:
        //location of the object
        btRigidBody* m_pBody;

    public:
        SimpleColliderComponent(void) : Component(invalidEntityID) {}
        SimpleColliderComponent(Entity_ID id, btRigidBody* pBody) 
            : Component(id), m_pBody(pBody) {}

        inline btRigidBody* getBody(void)
        {
            return m_pBody;
        }

        static const eComponentType m_componentType = eComponentType::ECS_COMP_SIMPLECOLLIDER;
    };
}

#endif //SIMPLECOLLIDERCOMPONENT_H_