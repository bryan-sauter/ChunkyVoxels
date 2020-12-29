#ifndef RENDERSET_H_
#define RENDERSET_H_

#include <vector>
#include "render/RenderNode.h"

class RenderSet
{
private:
    vector<RenderNode*> m_vRenderSet;

public:
    RenderSet(void);
    ~RenderSet(void);
    void addRenderNode(RenderNode* pRenderNode);
    RenderNode* getRenderNode(const unsigned int uiIndex);
    vector<RenderNode*>::iterator getBeginIterator(void);
    vector<RenderNode*>::iterator getEndIterator(void);
    //This function will not dump the pointers, object manager is responsible
    //for the memory management of the nodes. Or a mesh manager, but currently
    //we are only doing cubes (single mesh).
    void clearRenderSet(void);
};


#endif //RENDERSET_H_
