#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stdafx.h"
#include <set>

#include "ecs/Entity.h"
#include "ecs/ECSTypes.h"

namespace ECS
{
    // forward declare to avoid circular include
    class World;
    // A system is defined as an "engine" or manipulator of components
    class System
    {
    private:
        // the types of components the world will send to this system
        ComponentTypeSet m_sysRegisteredComponents;
        // having a nullptr to the world is not valid
        System(void) : m_world(nullptr) {}
        // child classes need access to the following
    protected:
        // TODO - revisit if this is needed/useful...event/listener might be a thing
        World* m_world;
        // the entities that this system needs to update and track
        set<Entity_ID> m_sysEntities;
        // child class should pass this from its constructor, a set of components this system wants
        inline void setRegisteredComponents(ComponentTypeSet&& registeredComponents)
        {
            m_sysRegisteredComponents = move(registeredComponents);
        }
        // on state changes we might want to reset our state, currently world does nothing
        // when this is called. Depending on future structuring that might be needed.
        inline void clearRegisteredComponents(void)
        {
            m_sysRegisteredComponents.clear();
        }
        // child class can send the enum/types individually for the components this system wants
        inline void addRegisteredComponents(eComponentType componentTypeID)
        {
            m_sysRegisteredComponents.insert(componentTypeID);
        }

    public:
        // constructor
        explicit System(World* world);
        // destructor - virtual to make sure is called on child destruction
        virtual ~System(void);
        // give access to the World to know what has been registered to this system
        inline const ComponentTypeSet& getRegisteredComponents(void) const
        {
            return m_sysRegisteredComponents;
        }
        // World will send the entities this system needs to register as they register with the World
        inline bool registerEntity(Entity_ID entity)
        {
            return m_sysEntities.insert(entity).second;
        }
        // called to remove the entity from the set of entities this system will update
        inline size_t unregisterEntity(Entity_ID entity)
        {
            return m_sysEntities.erase(entity);
        }
        // returns true if this system has this entity
        inline bool hasEntity(Entity_ID entity)
        {
            return (m_sysEntities.end() != m_sysEntities.find(entity));
        }
        // called every frame to update the entities manipulated by this system
        void updateEntities(float fDt);
        // actual implementation for how each entity should be manipulated
        // TODO - subclass needs entity since we aren't using pairs of tuples
        // should this be explicit to what exactly the subclass will manipulate?
        // subclass will have access to the World to pull all components of an entity
        virtual void updateEntity(float fDt, ECS::Entity_ID pEntity) = 0;
    };
}

#endif //SYSTEM_H_
