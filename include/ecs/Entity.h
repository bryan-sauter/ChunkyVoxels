#ifndef ENTITY_H_
#define ENTITY_H_

#include "stdafx.h"

namespace ECS {
    //this was previously defined as a class, that was useless at this point
    typedef size_t Entity_ID;
    static const Entity_ID invalidEntityID = 0u;
    static const Entity_ID maxEntityID = SIZE_MAX;
}

#endif //ENTITY_H_
