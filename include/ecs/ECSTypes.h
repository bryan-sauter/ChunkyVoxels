#ifndef ECSTYPES_H_
#define ECSTYPES_H_

#include "stdafx.h"
#include <set>

namespace ECS
{
    //hide the typing from downstream users
    typedef unsigned int ComponentType_ID;
    typedef set<ComponentType_ID> ComponentTypeSet;
    enum class eComponentType
    {
        COMP_INVALID = 0,
        COMP_TRANSFORM,
        COMP_RENDERABLE,
        COMP_COLLIDABLE,

    };
}

#endif //ECSTYPES_H_