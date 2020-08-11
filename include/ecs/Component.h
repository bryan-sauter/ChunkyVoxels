#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ECSTypes.h"

namespace ECS
{
    class Component
    {
    private:
        Component(void);
    public:
        Component(eComponentType componentType) : m_componentType(static_cast<ComponentType_ID>(componentType)) {}
        const ComponentType_ID m_componentType;
    };
}

#endif //COMPONENT_H_
