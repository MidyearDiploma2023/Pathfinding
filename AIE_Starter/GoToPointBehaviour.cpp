#include "GoToPointBehaviour.h"
#include "raylib.h"
#include "glm/glm.hpp"
#include "Agent.h"

namespace AIForGames
{
	void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (IsMouseButtonPressed(0))
		{
			Vector2 mousePos = GetMousePosition();
			agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
		}
	}
}