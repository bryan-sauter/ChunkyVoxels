#ifndef RENDERNODE_H_
#define RENDERNODE_H_

#include "stdafx.h"

//This rendernode will probably be owned by a renderable object
//Any information the renderer needs to draw the object should be 
//self contained to this class
class RenderNode
{
private:
    glm::vec3 m_vPosition;

public:
    RenderNode(void);
    RenderNode(float fX, float fY, float fZ);
    glm::vec3 getPosition(void);
    void setPosition(glm::vec3 vPosition);
    void setPosition(float fX, float fY, float fZ);
};

#endif //RENDERNODE_H_
