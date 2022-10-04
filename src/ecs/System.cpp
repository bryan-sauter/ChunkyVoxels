#include "ecs/System.h"

namespace ECS
{
    System::System(World* world) : m_world(world)
    {
    }

    System::~System(void)
    {
    }
    // loop through the entities and call the systems update on them
    void System::updateEntities(double fDt)
    {
        for (auto entity : m_sysEntities)
        {
            // call the pure virtual function that should be defined by the child class
            updateEntity(fDt, entity);
        }
    }
}
