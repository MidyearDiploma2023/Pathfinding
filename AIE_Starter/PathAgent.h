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
		//PathAgent() {}
		PathAgent(NodeMap* nodeMap);
		void Update(float deltaTime);
		void GoToNode(Node* node);
		void Draw();
		void SetNode(Node* node);
		void SetSpeed(float speed);
		bool IsEmpty();
		glm::vec2 GetPosition();
		void Reset();
		void SetColor(Color c);
	protected:
	private:
		glm::vec2 m_position;
		std::vector<Node*> m_path;
		int m_currentIndex;
		Node* m_currentNode;
		float m_speed;
		NodeMap* nodeMap;
		Color m_color;
	};
}