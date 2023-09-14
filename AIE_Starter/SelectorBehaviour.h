#pragma once
#include "Behaviour.h"

namespace AIForGames
{
    class SelectorBehaviour :
        public Behaviour
    {
    private:
        Behaviour* m_b1;
        Behaviour* m_b2;
        Behaviour* m_selected;
    public:
        SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
        ~SelectorBehaviour() { delete m_b1; delete m_b2; }
        void SetBehaviour(Behaviour* b, Agent* agent);
        virtual void Update(Agent* agent, float deltaTime);
    };
}
