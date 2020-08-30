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
    "CompClass must be a valid ComponentType\n");

namespace ECS
{
    class IComponentStorage
    {
    public:
        virtual ~IComponentStorage(void) {}
        //container class to allow the world to store a raw pointer (old school sorry)
        virtual void destroyAndRemove(const Entity_ID entity) = 0;
        virtual void destroy(void) = 0;
    };
    template<typename CompClass>
    class ComponentStorage : public IComponentStorage
    {
        // allows for the scope resolution operator of the ComponentType_ID from templated class
        ASSERT_COMPONENT_STORAGE;
    private:
        // the mapping for entity->components for this storages type
        vector<CompClass*> m_compStore;
        typename vector<CompClass*>::iterator m_storeIter;
        // defines what type of component this storage instance is keeping
        static const eComponentType m_compType = CompClass::m_componentType;
    public:
        ComponentStorage(void) {}
        ~ComponentStorage(void) { destroy(); }
        // store a pair in our map of an entity to its component of this type
        inline bool add(CompClass* component)
        {
            if (component->getEntityID() != invalidEntityID)
            {
                this->m_compStore.push_back(component);
                return true;
            }
            return false;
        }
        // remove and destroy (delete) the component then remove our reference to the entity
        inline void destroyAndRemove(const Entity_ID entity)
        {
            auto entityToDestroy = find(entity);
            if (entityToDestroy != m_compStore.end())
            {
                m_compStore.erase(entityToDestroy);
                //TODO - pool usage would need to be 
                auto componentToDestroy = *entityToDestroy;
                if (componentToDestroy)
                {
                    SAFE_DELETE(componentToDestroy);
                }
            }
        }
        // returns true if the entity exists in the map
        inline bool has(const Entity_ID entity)
        {
            m_storeIter = find(entity);
            return (m_storeIter != m_compStore.end());
        }
        // returns the component pointer to the passed entity
        inline CompClass* get(const Entity_ID entity)
        {
            m_storeIter = find(entity);
            return (m_storeIter != m_compStore.end()) ? *m_storeIter : nullptr;
        }
        // returns the component storage core map
        inline const vector<CompClass*> getStoredComponents(void)
        {
            return this->m_compStore;
        }
        inline void destroy(void)
        {
            for (auto C : m_compStore)
            {
                SAFE_DELETE(C);
            }
            m_compStore.clear();
        }
        inline typename vector<CompClass*>::iterator find(const Entity_ID entity)
        {
            for (m_storeIter = m_compStore.begin(); m_storeIter != m_compStore.end(); ++m_storeIter)
            {
                if ((*m_storeIter)->getEntityID() == entity)
                {
                    break;
                }
            }
            return m_storeIter;
        }
    };
}


#endif //COMPONENTSTORAGE_H_

