#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ecs/ECSTypes.h"

namespace ECS
{
    // base class to all components of the Entity Component System
    class Component
    {
    private:

    public:
        // TODO - Define the core interfaces we need, just the constructor? OnCreate? OnDestroy?
        Component(void) {}
        virtual ~Component(void) {}
        static const eComponentType m_componentType = eComponentType::ECS_COMP_INVALID;
    };
}

#endif //COMPONENT_H_
