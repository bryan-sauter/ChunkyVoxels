#ifndef COMPONENTSTORAGE_H_
#define COMPONENTSTORAGE_H_

#include "stdafx.h"
#include "helpers/HResultHelpers.h"
#include <unordered_map>

#include "ecs/Entity.h"
#include "ecs/Component.h"

// macro to make sure our templated usages can be updated in one central place
#define ASSERT_COMPONENT_STORAGE \
static_assert(is_base_of<Component, CompClass>::value, "CompClass needs to be derived from Component\n"); \
static_assert(CompClass::m_componentType != ECS::eComponentType::ECS_COMP_INVALID, \
    "CompClass must be a valid ComponentType\n")

namespace ECS
{
    class IComponentStorage
    {
    public:
        virtual ~IComponentStorage(void) {}
        //container class to allow the world to store a raw pointer (old school sorry)
        virtual bool destroyAndRemove(const Entity_ID entity) = 0;
        virtual void destroy(void) = 0;
    };
    template<typename CompClass>
    class ComponentStorage : public IComponentStorage
    {
        // allows for the scope resolution operator of the ComponentType_ID from templated class
        ASSERT_COMPONENT_STORAGE;
    private:
        // the mapping for entity->components for this storages type
        unordered_map<Entity_ID, CompClass*> m_compStoreMap;
        // defines what type of component this storage instance is keeping
        static const eComponentType m_compType = CompClass::m_componentType;
    public:
        ComponentStorage(void) {}
        ~ComponentStorage(void) { destroy(); }
        // store a pair in our map of an entity to its component of this type
        inline bool add(const Entity_ID entity, CompClass* component)
        {
            return this->m_compStoreMap.insert(make_pair(entity,component)).second;
        }
        // remove and destroy (delete) the component then remove our reference to the entity
        inline bool destroyAndRemove(const Entity_ID entity)
        {
            auto entityToDestroy = m_compStoreMap.find(entity);
            if (entityToDestroy != m_compStoreMap.end())
            {
                //TODO - pool usage would need to be 
                auto componentToDestroy = (*entityToDestroy).second;
                if (componentToDestroy)
                {
                    SAFE_DELETE(componentToDestroy);
                }
            }
            return (0 < this->m_compStoreMap.erase(entity));
        }
        // returns true if the entity exists in the map
        inline bool has(const Entity_ID entity)
        {
            return (this->m_compStoreMap.end() != this->m_compStoreMap.find(entity));
        }
        // returns the component pointer to the passed entity
        inline CompClass* get(const Entity_ID entity)
        {
            return this->m_compStoreMap.at(entity);
        }
        // returns the component storage core map
        inline const unordered_map<Entity_ID, CompClass*> getStoredComponents(void)
        {
            return this->m_compStoreMap;
        }
        inline void destroy(void)
        {
            for (auto C : m_compStoreMap)
            {
                delete C.second;
            }
        }
    };
}


#endif //COMPONENTSTORAGE_H_

