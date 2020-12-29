#include "..\..\include\render\RenderSet.h"

RenderSet::RenderSet(void)
{
}

RenderSet::~RenderSet(void)
{
}

void RenderSet::addRenderNode(RenderNode* pRenderNode)
{
    if (pRenderNode != nullptr)
    {
        m_vRenderSet.push_back(pRenderNode);
    }
}

RenderNode* RenderSet::getRenderNode(const unsigned int uiIndex)
{
    if (uiIndex < m_vRenderSet.size())
    {
        return m_vRenderSet[uiIndex];
    }
    return nullptr;
}

vector<RenderNode*>::iterator RenderSet::getBeginIterator(void)
{
    return this->m_vRenderSet.begin();
}

vector<RenderNode*>::iterator RenderSet::getEndIterator(void)
{
    return this->m_vRenderSet.end();
}

void RenderSet::clearRenderSet(void)
{
    if (m_vRenderSet.size() > 0)
    {
        m_vRenderSet.clear();
    }
}
