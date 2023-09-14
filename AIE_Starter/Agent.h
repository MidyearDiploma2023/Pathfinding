#pragma once

#include "raylib.h"
#include "PathAgent.h"

namespace AIForGames
{
	class Behaviour;
	class NodeMap;

	class Agent
	{
	public:
		Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255,255,0,255 }), m_pathAgent(_nodeMap) { m_pathAgent.SetSpeed(128); }
		~Agent() { delete m_current; }

		void Update(float deltaTime);
		void Draw();
		void GoTo(glm::vec2 point);
		void SetNode(Node* node);
	protected:
	private:
		PathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_color;
	};
}