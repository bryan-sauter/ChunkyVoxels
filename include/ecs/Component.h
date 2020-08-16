#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ecs/ECSTypes.h"

namespace ECS
{
    // base class to all components of the Entity Component System
    class Component
    {
    private:
        // default constructor is not a valid component creation method
        Component(void) : m_componentType(ECS_COMP_INVALID) {}
    public:
        // TODO - Define the core interfaces we need, just the constructor? OnCreate? OnDestroy?
        Component(eComponentType componentType) : m_componentType(componentType) {}
        const ComponentType_ID m_componentType;
    };
}

#endif //COMPONENT_H_
