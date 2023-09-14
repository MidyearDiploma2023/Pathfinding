#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include "glm/glm.hpp"

namespace AIForGames
{
    class FollowBehaviour :
        public Behaviour
    {
    public:
        virtual void Update(Agent* agent, float deltaTime);
    private:
        glm::vec2 lastTargetPosition;
    };
}
