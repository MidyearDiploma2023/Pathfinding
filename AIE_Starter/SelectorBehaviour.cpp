#include "SelectorBehaviour.h"
#include "Agent.h"
#include "Pathfinding.h"

namespace AIForGames
{
	void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
	{
		if (m_selected != b)
		{
			m_selected = b;
			agent->Reset();
		}
	}
	void SelectorBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (glm::length(agent->GetPosition() - agent->GetTargetAgent()->GetPosition()) < agent->GetNodeMap()->GetCellSize() * 5)
		{
			SetBehaviour(m_b1, agent);
			agent->SetColor({ 255,0,0,255 });
		}
		else
		{
			SetBehaviour(m_b2, agent);
			agent->SetColor({ 0,255,255,255 });
		}
		m_selected->Update(agent, deltaTime);
	}
}