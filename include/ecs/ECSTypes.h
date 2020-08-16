#ifndef ECSTYPES_H_
#define ECSTYPES_H_

#include "stdafx.h"
#include <set>

namespace ECS
{
    // hide the typing from downstream users
    // simple unsigned ints are fine, enum is for readability
    typedef unsigned int ComponentType_ID;
    typedef set<ComponentType_ID> ComponentTypeSet;
    enum eComponentType
    {
        ECS_COMP_INVALID = 0,
        ECS_COMP_TRANSFORM,
        ECS_COMP_RENDERABLE,
        ECS_COMP_COLLIDABLE,

    };
}

#endif //ECSTYPES_H_