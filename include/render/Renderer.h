#ifndef RENDERER_H_
#define RENDERER_H_

#include "render/Camera.h"

class Renderer {
protected:
    Camera m_Camera;

public:
    virtual bool initialize(void) = 0;
    virtual void update(float dT) = 0;
    virtual void render(void) = 0;
    virtual bool shutdown(void) = 0;
};
#endif //RENDERER_H_
