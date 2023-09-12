#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "raylib.h"
namespace AIForGames
{
	struct Node;
	class NodeMap;
	class PathAgent
	{
	public:
		PathAgent(NodeMap* nodeMap);
		void Update(float deltaTime);
		void GoToNode(Node* node);
		void Draw();
		void SetNode(Node* node);
		void SetSpeed(float speed);
		void SetColor(Color color);
		float GetSpeed() { return m_speed; }
	protected:
	private:
		glm::vec2 m_position;
		std::vector<Node*> m_path;
		int m_currentIndex;
		Node* m_currentNode;
		float m_speed;
		NodeMap* nodeMap;
		Color m_color;
		void FindRandomPath();
	};
}