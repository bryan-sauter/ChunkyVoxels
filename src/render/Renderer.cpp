#include "render/Renderer.h"

void Renderer::addRenderNode(RenderNode* pRenderNode)
{
    m_RenderSet.addRenderNode(pRenderNode);
}

void Renderer::clearRenderSet(void)
{
    m_RenderSet.clearRenderSet();
}
