#ifndef WORLD_H_
#define WORLD_H_

#include "stdafx.h"

#include <map>

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "ecs/ComponentStorage.h"

namespace ECS
{
    // Container for all entities and components currently valid
    // A component manager or memory might be needed in tandem with this container
    class World
    {
    private:
        // the current set of systems registered to the world to do work
        vector<System*> m_vSystems;
        // the component storage bundles, type->all components of type
        map<eComponentType, IComponentStorage*> m_componentStorage;
        // the entities and what component types they have associated with them
        unordered_map<Entity_ID, ComponentTypeSet> m_EntityRegisters;
        // infinitely incrementing counter for the last entity ID used
        Entity_ID m_lastEntityID;
    public:
        World(void);
        ~World(void);
        /*
         * create a component storage space for components of the type used
         * should be possible to bundle this call into the first call of addComponent
         */
        template<typename CompClass>
        inline bool createComponentStorage(void)
        {
            //allows for the scope resolution operator of the ComponentType_ID from templated class
            ASSERT_COMPONENT_STORAGE;
            //pair the component type with the new storagae class
            IComponentStorage* store = new ComponentStorage<CompClass>();
            return this->m_componentStorage.insert(
                make_pair(CompClass::m_componentType, store)).second;
        }
        /*
         * get the component storage for the templated type, create one if it doesn't exist
         */
        template<typename CompClass>
        inline ComponentStorage<CompClass>* getComponentStorage(void)
        {
            ASSERT_COMPONENT_STORAGE;
            auto iCompStore = m_componentStorage.find(CompClass::m_componentType);
            if (m_componentStorage.end() == iCompStore)
            {
                if (createComponentStorage<CompClass>())
                {
                    return getComponentStorage<CompClass>();
                }
            }
            return dynamic_cast<ComponentStorage<CompClass>*>(iCompStore->second);
        }
        /*
         * add a component to a component storage container
         */
        template<typename CompClass>
        inline bool addComponent(const Entity_ID entity, CompClass* component)
        {
            ASSERT_COMPONENT_STORAGE;
            auto registeredEntity = m_EntityRegisters.find(entity);
            if (registeredEntity == m_EntityRegisters.end())
            {
                throw runtime_error("Entity_ID was not found\n");
            }
            (*registeredEntity).second.insert(CompClass::m_componentType);
            return getComponentStorage<CompClass>()->add(entity, component);
        }
        /*
         * add a system to the World
         */
        void addSystem(System* system);
        /*
         * register an entity to be manipulated by the ECS
         */
        size_t registerEntity(const Entity_ID entity);
        /*
         * unregister an entity and kill off all components currently inuse by it
         */
        size_t unregisterEntity(const Entity_ID entity);
        /*
         * loop through all the systems and update their entities
         */
        void updateEntities(float fDt);
        /*
         * get the next valid ID
         */
        Entity_ID createEntity(void);
        /*
         * destroy and entity along with everything it stands for
         */
        void destroyEntity(const Entity_ID entity);
        //very ominous sounding, lets clean up our memory usage
        void destoryWorld(void);
    };
}

#endif //WORLD_H_

