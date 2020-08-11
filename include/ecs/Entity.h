#ifndef ENTITY_H_
#define ENTITY_H_

#include "stdafx.h"

namespace ECS {

    typedef unsigned int Entity_ID;
    static const Entity_ID invalidEntityID = 0u;
    //this class could be a basic uint, just for future proofing I am defining a class
    //this could be boiled down to a typedef or using statement, to each their own
    class Entity
    {
    private:
        //you cannot create an entity without defining the ID
        Entity(void) : m_entityID(invalidEntityID) {}
    public:
        //define who I am
        Entity_ID m_entityID;
        //create me
        Entity(Entity_ID entityID);
    };
}

#endif //ENTITY_H_
