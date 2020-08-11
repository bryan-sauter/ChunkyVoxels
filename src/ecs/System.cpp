#include "ecs/System.h"

namespace ECS
{
    System::System(World* world) : m_world(world)
    {
    }

    System::~System(void)
    {
    }

    void System::updateEntities(float fDt)
    {
        for (auto entity = m_sysEntities.begin();
            entity != m_sysEntities.end();
            ++entity)
        {
            updateEntity(fDt, *entity);
        }
    }
}
