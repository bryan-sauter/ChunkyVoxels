#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "stdafx.h"
#include "ecs/Component.h"
#include "ecs/ECSTypes.h"

namespace ECS
{
    class TransformComponent : public Component
    {
    private:
        glm::vec3 m_vPosition;

    public:
        TransformComponent(glm::vec3 vPosition)
        {
            setPosition(vPosition);
        }
        TransformComponent(float fX, float fY, float fZ)
        {
            setPosition(fX, fY, fZ);
        }
        inline glm::vec3 getPosition(void)
        {
            return this->m_vPosition;
        }
        inline void setPosition(glm::vec3 vPosition)
        {
            this->m_vPosition = vPosition;
        }
        inline void setPosition(float fX, float fY, float fZ)
        {
            this->m_vPosition.x = fX;
            this->m_vPosition.y = fY;
            this->m_vPosition.z = fZ;
        }

        static const eComponentType m_componentType = eComponentType::ECS_COMP_TRANSFORM;
    };
}

#endif //TRANSFORMCOMPONENT_H_
