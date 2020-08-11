#include "render\RenderNode.h"

RenderNode::RenderNode(void) : m_vPosition(glm::vec3(0.0f,0.0f,0.0f))
{
}

RenderNode::RenderNode(float fX, float fY, float fZ)
{
    this->setPosition(fX, fY, fZ);
}

glm::vec3 RenderNode::getPosition(void)
{
    return this->m_vPosition;
}

void RenderNode::setPosition(glm::vec3 vPosition)
{
    this->m_vPosition = vPosition;
}

void RenderNode::setPosition(float fX, float fY, float fZ)
{
    this->m_vPosition.x = fX;
    this->m_vPosition.y = fY;
    this->m_vPosition.z = fZ;
}
