#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ecs/ECSTypes.h"

namespace ECS
{
    // base class to all components of the Entity Component System
    class Component
    {
    private:

    protected:
        Entity_ID m_entityID;
    public:
        // TODO - Define the core interfaces we need, just the constructor? OnCreate? OnDestroy?
        Component(Entity_ID id) : m_entityID(id) {}
        virtual ~Component(void) {}
        static const eComponentType m_componentType = eComponentType::ECS_COMP_INVALID;

        inline const Entity_ID getEntityID(void)
        {
            return m_entityID;
        }
    };
}

#endif //COMPONENT_H_
