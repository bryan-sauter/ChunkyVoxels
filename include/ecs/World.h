#ifndef WORLD_H_
#define WORLD_H_

#include "stdafx.h"
#include "ecs/Entity.h"

#include <vector>

namespace ECS
{
    class World
    {
    private:

    public:
        World(void);
        virtual ~World(void);
    };
}

#endif //WORLD_H_

