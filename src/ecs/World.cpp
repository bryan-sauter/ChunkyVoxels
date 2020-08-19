#include "ecs/World.h"

#include <algorithm>

namespace ECS
{
    World::World(void) : m_lastEntityID(invalidEntityID),
        m_componentStorage(),
        m_EntityRegisters(),
        m_vSystems()
    {
    }
    World::~World(void)
    {
        destoryWorld();
    }
    void World::addSystem(System* system)
    {
        if (!system || system->getRegisteredComponents().empty())
        {
            throw runtime_error("System is not registered to any components\n");
        }
        m_vSystems.push_back(system);
    }
    size_t World::registerEntity(const Entity_ID entity)
    {
        size_t nRegisteredSystems = 0;

        auto entityToRegister = m_EntityRegisters.find(entity);
        if (entityToRegister == m_EntityRegisters.end()) {
            throw std::runtime_error("The Entity does not exist");
        }
        auto entityComponents = (*entityToRegister).second;

        // via the currently registered systems check to see who is interested in this entity
        for (auto system : m_vSystems) {
            auto systemRegisteredComponents = system->getRegisteredComponents();
            // make sure the entity has all the components a system needs to manipulate it
            if (std::includes(entityComponents.begin(), entityComponents.end(),
                systemRegisteredComponents.begin(), systemRegisteredComponents.end())) {
                // tell the system there is a new entity it needs to track
                system->registerEntity(entity);
                ++nRegisteredSystems;
            }
        }
        return nRegisteredSystems;
    }
    size_t World::unregisterEntity(const Entity_ID entity)
    {
        size_t nUnregisteredSystems = 0;
        //check to make sure the entity was previously registered
        auto registeredEntity = m_EntityRegisters.find(entity);
        if (registeredEntity == m_EntityRegisters.end())
        {
            //debatable if I will throw an error or not, typically this would be a 
            //case where the entity is already dead and should be a no op.
            //however it might identify errors in pooling once that is added
            throw runtime_error("Attempted to unregister entity that did not exist\n");
        }

        for (auto system : m_vSystems)
        {
            nUnregisteredSystems += system->unregisterEntity(entity);
        }
        return nUnregisteredSystems;
    }
    void World::updateEntities(float fDt)
    {
        //loop through the current systems and let them update their entities
        for (auto system : m_vSystems)
        {
            system->updateEntities(fDt);
        }
    }
    Entity_ID World::createEntity(void)
    {
        assert(m_lastEntityID < maxEntityID);
        m_EntityRegisters.insert(make_pair(Entity_ID(m_lastEntityID + 1), ComponentTypeSet()));
        return (++m_lastEntityID);
    }
    void World::destroyEntity(const Entity_ID entity)
    {
        auto registeredEntity = m_EntityRegisters.find(entity);
        if (registeredEntity == m_EntityRegisters.end())
        {
            throw runtime_error("Entity_ID was not found\n");
        }
        ComponentTypeSet compSet = (*registeredEntity).second;

        for (auto compType : compSet)
        {
            auto store = m_componentStorage.find(compType);
            if (store != m_componentStorage.end())
            {
                (*store).second->destroyAndRemove(entity);
            }
        }
    }
    void World::destoryWorld(void)
    {
        for (auto storage : m_componentStorage)
        {
            SAFE_DELETE(storage.second);
        }
    }
}