#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stdafx.h"
#include "ecs/World.h"
#include "ecs/ECSTypes.h"

#include <set>

namespace ECS
{
    class System
    {
    private:
        set<Entity_ID> m_sysEntities;
        ComponentTypeSet m_sysRegisteredComponents;

        
        System(void) : m_world(nullptr) {}

    protected:
        World* m_world;

        inline void setRegisteredComponents(ComponentTypeSet&& registeredComponents)
        {
            m_sysRegisteredComponents = move(registeredComponents);
        }
        inline void clearRegisteredComponents(void)
        {
            m_sysRegisteredComponents.clear();
        }
        inline void addRegisteredComponents(ComponentType_ID componentTypeID)
        {
            m_sysRegisteredComponents.insert(componentTypeID);
        }

    public:
        explicit System(World* world);

        virtual ~System(void);
        //give access to the World to know what has been registered to this system
        inline const ComponentTypeSet& getRegisteredComponents(void) const
        {
            return m_sysRegisteredComponents;
        }
        inline bool registerEntity(Entity_ID entity)
        {
            return m_sysEntities.insert(entity).second;
        }
        inline unsigned int unregisterEntity(Entity_ID entity)
        {
            return (unsigned int)m_sysEntities.erase(entity);
        }
        inline bool hasEntity(Entity_ID entity)
        {
            return (m_sysEntities.end() != m_sysEntities.find(entity));
        }

        void updateEntities(float fDt);
        virtual void updateEntity(float fDt, ECS::Entity_ID pEntity) = 0;
    };
}

#endif //SYSTEM_H_
