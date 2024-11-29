#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "stdafx.h"
#include "ecs/Component.h"
#include "ecs/ECSTypes.h"

using namespace DirectX;

namespace ECS
{
    class TransformComponent : public Component
    {
    private:
        glm::vec3 m_vPosition;
        glm::vec4 m_vRotation;

        XMMATRIX m_mmObjectTransform;

        inline void updateTransform(void)
        {
            XMFLOAT4 tempv4 = XMFLOAT4(m_vRotation.x, m_vRotation.y, m_vRotation.z, m_vRotation.w);
            XMMATRIX translation = XMMatrixTranslation(m_vPosition.x, m_vPosition.y, m_vPosition.z);
            XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&tempv4));
            m_mmObjectTransform = rotation * translation;
        }

    public:
        TransformComponent(void) : Component(invalidEntityID), m_vPosition(0.0f) {}
        TransformComponent(Entity_ID id, glm::vec3 vPosition) : Component(id)
        {
            setPosition(vPosition);
            m_mmObjectTransform = XMMatrixIdentity();
        }
        TransformComponent(Entity_ID id, float fX, float fY, float fZ) : Component(id)
        {
            setPosition(fX, fY, fZ);
        }
        inline glm::vec3 getPosition(void)
        {
            return this->m_vPosition;
        }
        inline glm::vec4 getRotation(void)
        {
            return this->m_vRotation;
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
            updateTransform();
        }        
        inline void setPosition(btVector3 vPosition)
        {
            this->m_vPosition.x = vPosition[0];
            this->m_vPosition.y = vPosition[1];
            this->m_vPosition.z = vPosition[2];
            updateTransform();
        }
        inline void setRotation(btQuaternion vRotation)
        {
            this->m_vRotation.w = vRotation[3];
            this->m_vRotation.x = vRotation[0];
            this->m_vRotation.y = vRotation[1];
            this->m_vRotation.z = vRotation[2];
            updateTransform();
        }
        inline void setPhysicsTransform(btVector3 vPosition, btQuaternion vRotation)
        {
            this->m_vPosition.x = vPosition[0];
            this->m_vPosition.y = vPosition[1];
            this->m_vPosition.z = vPosition[2];
            this->m_vRotation.w = vRotation[3];
            this->m_vRotation.x = vRotation[0];
            this->m_vRotation.y = vRotation[1];
            this->m_vRotation.z = vRotation[2];
            updateTransform();
        }
        inline XMMATRIX getTransformMatrix(void)
        {
            return m_mmObjectTransform;
        }

        static const eComponentType m_componentType = eComponentType::ECS_COMP_TRANSFORM;
    };
}

#endif //TRANSFORMCOMPONENT_H_
