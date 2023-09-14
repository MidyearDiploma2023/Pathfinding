#include "WanderBehaviour.h"
#include "Agent.h"
namespace AIForGames
{
	void WanderBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (agent->PathComplete())
			agent->GoTo(agent->GetRandomNode());
	}
}