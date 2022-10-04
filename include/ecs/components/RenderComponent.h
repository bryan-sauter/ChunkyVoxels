#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "stdafx.h"
#include "ecs/Component.h"
#include "ecs/ECSTypes.h"
#include "ecs/Entity.h"
#include "ecs/components/TransformComponent.h"

#include "render/D3D11Render/D3D11TextureHandle.h"

namespace ECS
{

    class RenderComponent : public Component
    {
    private:
        Texture_ID m_textureID;
        //provide read-only access to this rendercomponents transform
        //we can have transform objects that don't render, hence why they aren't coupled into one
        TransformComponent* m_pTransform;

    public:
        RenderComponent(void) : Component(invalidEntityID), m_textureID(defaultTextureID),
                                m_pTransform(nullptr)
        {}
        RenderComponent(Entity_ID id, Texture_ID textureID, TransformComponent* pTransform) :
            Component(id), m_textureID(textureID), m_pTransform(pTransform) {}
        inline Texture_ID getTextureID(void)
        {
            return m_textureID;
        }
        inline void setTextureID(Texture_ID textureID)
        {
            this->m_textureID = textureID;
        }
        inline XMMATRIX getTransformMatrix(void)
        {
            return m_pTransform ? m_pTransform->getTransformMatrix() : XMMatrixIdentity();
        }


        static const eComponentType m_componentType = eComponentType::ECS_COMP_RENDERABLE;
    };
}

#endif //RENDERCOMPONENT_H_