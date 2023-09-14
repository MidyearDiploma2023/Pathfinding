#pragma once
#include "Behaviour.h"
namespace AIForGames
{
    class GoToPointBehaviour :
        public Behaviour
    {
    public:
        virtual void Update(Agent* agent, float deltaTime);
    };
}

