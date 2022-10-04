#ifndef RENDERER_H_
#define RENDERER_H_

#include "render/Camera.h"
#include "render/RenderSet.h"
#include "render/D3D11Render/D3D11Camera.h"

class Renderer {
protected:
    RenderSet m_RenderSet;
public:
    virtual ~Renderer(void) {}
    virtual bool initialize(void) = 0;
    virtual void update(double dT) = 0;
    virtual void render(void) = 0;
    virtual bool shutdown(void) = 0;
    virtual D3D11Camera* getCamera(void) = 0;
    //virtual Camera* getCamera(void) = 0;
    //shielding from direct access to the renderset
    void addRenderNode(RenderNode* pRenderNode);
    void clearRenderSet(void);
};
#endif //RENDERER_H_
