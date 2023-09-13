#include "PathAgent.h"
#include "Pathfinding.h"
#include <iostream>
AIForGames::PathAgent::PathAgent(NodeMap* nodeMap)
{
	this->nodeMap = nodeMap;
	m_currentIndex = 0;
	m_currentNode = nullptr;
	m_speed = 2.0f;
	m_color = YELLOW;
	m_position = glm::vec2(0, 0);
}

void AIForGames::PathAgent::Update(float deltaTime)
{
	if (deltaTime > 1)
	{
		return;
	}
	if (m_path.size() == 0)
	{
		GoToNode(nodeMap->GetRandomNode());
		//FindRandomPath();
		return;
	}

	glm::vec2 offsetDelta = m_path[m_currentIndex]->position - m_position;

	float distance = glm::length(offsetDelta);
	float step = m_speed * deltaTime;

	float moveDelta = distance - step;
	if (moveDelta > 0) m_position += step * glm::normalize(offsetDelta);
	else
	{
		m_currentNode = m_path[m_currentIndex];
		m_position = m_path[m_currentIndex]->position;
		m_currentIndex++;
		if (m_currentIndex == m_path.size())
		{
			m_path.clear();
			return;
		}

		moveDelta *= -1;
		offsetDelta = m_path[m_currentIndex]->position - m_position;
		m_position += moveDelta * glm::normalize(offsetDelta);
	}
}

void AIForGames::PathAgent::GoToNode(Node* node)
{
	m_path = nodeMap->DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void AIForGames::PathAgent::Draw()
{
	
	if (m_path.empty()) return;
	for (int i = m_currentIndex + 1; i < m_path.size(); i++) {
		DrawLine(m_path[i]->position.x, m_path[i]->position.y, m_path[i - 1]->position.x, m_path[i - 1]->position.y, m_color);
	}
}

void AIForGames::PathAgent::LateDraw()
{
	DrawCircle((int)m_position.x, (int)m_position.y, 8, m_color);
}

void AIForGames::PathAgent::SetNode(Node* node)
{
	m_currentNode = node;
	m_position = m_currentNode->position;
}

void AIForGames::PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}

void AIForGames::PathAgent::SetColor(Color color)
{
	m_color = color;
}

void AIForGames::PathAgent::FindRandomPath()
{
	Node* n = nullptr;
	while (n == nullptr)
	{
		n = nodeMap->GetClosestNode(glm::vec2(rand() % GetScreenWidth(), rand() % GetScreenHeight()));
	}
	GoToNode(n);
}
