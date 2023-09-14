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
		void GoTo(Node* node);
		void SetNode(Node* node);
		bool PathComplete();
		Node* GetRandomNode();
		Agent* GetTargetAgent();
		void SetTargetAgent(Agent* agent);
		glm::vec2 GetPosition();
		NodeMap* GetNodeMap();
		void SetColor(Color c);
		void SetSpeed(float s);
		void Reset();
	protected:
	private:
		PathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Agent* m_targetAgent;
		Color m_color;
	};
}