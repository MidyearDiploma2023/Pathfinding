#include "PathAgent.h"
#include "Pathfinding.h"
#include "raylib.h"
#include <iostream>
AIForGames::PathAgent::PathAgent(NodeMap* nodeMap)
{
	this->nodeMap = nodeMap;
	m_currentIndex = 0;
	m_speed = 2.0f;
}

void AIForGames::PathAgent::Update(float deltaTime)
{
	if (m_path.empty()) return;

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
	DrawCircle((int)m_position.x, (int)m_position.y, 8, { 255,255,0,255 });
	if (m_path.empty()) return;
	for (int i = m_currentIndex + 1; i < m_path.size(); i++) {
		DrawLine(m_path[i]->position.x, m_path[i]->position.y, m_path[i - 1]->position.x, m_path[i - 1]->position.y, GREEN);
	}
}

void AIForGames::PathAgent::SetNode(Node* node)
{
	m_currentNode = node;
	m_position = node->position;
}

void AIForGames::PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}
