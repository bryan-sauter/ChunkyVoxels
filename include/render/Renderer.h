#ifndef RENDERER_H_
#define RENDERER_H_

#include "render/Camera.h"
#include "render/D3D11Render/D3D11Camera.h"

class Renderer {
public:
    virtual bool initialize(void) = 0;
    virtual void update(float dT) = 0;
    virtual void render(void) = 0;
    virtual bool shutdown(void) = 0;
    virtual D3D11Camera* getCamera(void) = 0;
    //virtual Camera* getCamera(void) = 0;
};
#endif //RENDERER_H_
