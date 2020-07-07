#ifndef RENDERER_H_
#define RENDERER_H_

class Renderer {

public:
    virtual bool initialize(void) = 0;
    virtual void update(float dT) = 0;
    virtual void render(void) = 0;
    virtual bool shutdown(void) = 0;
};
#endif //RENDERER_H_
