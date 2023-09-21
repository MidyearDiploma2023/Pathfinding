#include "Pathfinding.h"
#include <iostream>
#include "raylib.h"
#include <queue>
namespace AIForGames
{
	void NodeMap::Intialise(std::vector<std::string> asciiMap, int cellSize)
	{
		this->cellSize = cellSize;
		const char emptySquare = '0';

		//assume all string are the same length, so we will size our map
		//according to the number of strings and the length of the first one
		height = asciiMap.size();
		width = asciiMap[0].size();

		mapSize = width * height;
		nodes = new Node * [width * height];

		//loop over our strings, creating node entries as we go 
		for (int y = 0; y < height; y++) {
			std::string& line = asciiMap[y];
			//report to the user if we  have a mis matching  string length 
			if (line.size() != width) {
				std::cout << "Mismatched line # " << y << " in the ASCII  map( " << line.size() << " instead of " << width << std::endl;
			}

			for (int x = 0; x < width; x++) {
				/* get the x-th character, or return an empty node if the string
				isnt long enough*/
				char tile = x < line.size() ? line[x] : emptySquare;

				//create a node for anthing but a '0' character 
				nodes[x + width * y] = tile == emptySquare ? nullptr : new Node((x + 0.5f) * cellSize, (y + 0.5f) * cellSize);

				if (nodes[x + width * y] != nullptr)
					m_allNodes.push_back(nodes[x + width * y]);
			}
		}

		/* Now loop over the nodes, creating connections between each node and its neighbour
		to its west and south on the grid, this will link every node*/
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Node* node = GetNode(x, y);
				if (node) {
					Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
					if (nodeWest) {
						node->ConnectTo(nodeWest, 1);
						nodeWest->ConnectTo(node, 1);
					}

					Node* nodeNorth = y == 0 ? nullptr : GetNode(x, y - 1);
					if (nodeNorth) {
						node->ConnectTo(nodeNorth, 1);
						nodeNorth->ConnectTo(node, 1);
					}
				}
			}
		}
		path = DijkstrasSearch(GetNode(1, 1), GetNode(10, 2));
	}

	Node* NodeMap::GetNode(int x, int y)
	{
		Node* node = x + width * y < mapSize ? nodes[x + width * y] : nullptr;
		return node;
	}
	Node* NodeMap::GetRandomNode()
	{
		return m_allNodes[rand() % m_allNodes.size()];
	}
	void NodeMap::Draw()
	{
		//Blue color for the walls
		Color cellColor = BLUE;
		Color lineColor = RED;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Node* node = GetNode(x, y);
				if (node == nullptr) {
					DrawRectangle((int)(x * cellSize), (int)(y * cellSize), (int)(cellSize - 1), (int)(cellSize - 1), cellColor);
				}
				/*else {
					for (int i = 0; i < node->connections.size(); i++) {
						Node* other = node->connections[i].target;
						DrawLine((x + 0.5f) * cellSize, (y + 0.5f) * cellSize, (int)other->position.x, (int)other->position.y, lineColor);
					}
				}*/
			}
		}

		//DrawRectangle((int)(path[0]->position.x - cellSize / 2), (int)(path[0]->position.y - cellSize / 2), (int)(cellSize - 1), (int)(cellSize - 1), MAGENTA);
		//DrawRectangle((int)(path[path.size() - 1]->position.x - cellSize / 2), (int)(path[path.size() - 1]->position.y - cellSize / 2), (int)(cellSize - 1), (int)(cellSize - 1), GREEN);
	}

	std::vector<Node*> NodeMap::DijkstrasSearch(Node* start, Node* end)
	{
		std::vector<Node*> path;
		if (start == nullptr || end == nullptr) {
			std::cout << "Start or end were nullptr" << std::endl;
			return path;
		}

		if (start == end) {
			return path;
		}

		//Reset nodes to base state, ready for pathfinding algorithm
		for (int i = 0; i < width * height; i++) {
			if (nodes[i] != nullptr) {
				nodes[i]->previous = nullptr;
				nodes[i]->gScore = 0;
			}
		}

		std::vector<Node*> openList;
		std::vector<Node*> closedList;
		Node* currentNode = nullptr;

		openList.push_back(start);

		while (!openList.empty())
		{
			auto comp = [&](Node* a, Node* b) {return a->gScore > b->gScore; };
			std::sort(openList.begin(), openList.end(), comp);

			//Assign the next node in the open list to be our current node
			currentNode = openList.back();
			//Removes the top of the queue from the queue
			openList.pop_back();

			//Adds the currentNode to the closed list so we dont process again
			closedList.push_back(currentNode);

			for (int i = 0; i < currentNode->connections.size(); i++)
			{
				if (std::find(closedList.begin(), closedList.end(), currentNode->connections[i].target) == std::end(closedList))
				{

					float gScore = currentNode->gScore + currentNode->connections[i].cost;

					if (std::find(openList.begin(), openList.end(), currentNode->connections[i].target) != std::end(openList))
					{
						//Node is already in the open list with a valid score 
						//so we need to compare the clculated score with the existing score 
						//to find the shorter path

						if (gScore < currentNode->connections[i].target->gScore)
						{
							currentNode->connections[i].target->gScore = gScore;
							currentNode->connections[i].target->previous = currentNode;
						}

					}
					else {

						currentNode->connections[i].target->gScore = gScore;
						currentNode->connections[i].target->previous = currentNode;
						openList.push_back(currentNode->connections[i].target);
					}
				}
			}
		}

		currentNode = end;
		while (currentNode != nullptr) {
			path.push_back(currentNode);
			currentNode = currentNode->previous;
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	std::vector<Node*> NodeMap::AStarSearch(Node* start, Node* end)
	{
		std::vector<Node*> path;
		if (start == nullptr || end == nullptr) {
			std::cout << "Start or end were nullptr" << std::endl;
			return path;
		}

		if (start == end) {
			return path;
		}

		//Reset nodes to base state, ready for pathfinding algorithm
		for (int i = 0; i < width * height; i++) {
			if (nodes[i] != nullptr) {
				nodes[i]->previous = nullptr;
				nodes[i]->gScore = 0;
				nodes[i]->hScore = 0;
				nodes[i]->fScore = 0;
			}
		}

		std::vector<Node*> openList;
		std::vector<Node*> closedList;
		Node* currentNode = nullptr;

		openList.push_back(start);

		while (!openList.empty())
		{
			auto comp = [&](Node* a, Node* b) {return a->fScore > b->fScore; };
			std::sort(openList.begin(), openList.end(), comp);

			//Assign the next node in the open list to be our current node
			currentNode = openList.back();
			//Removes the top of the queue from the queue
			openList.pop_back();

			//Adds the currentNode to the closed list so we dont process again
			closedList.push_back(currentNode);

			for (int i = 0; i < currentNode->connections.size(); i++)
			{
				if (std::find(closedList.begin(), closedList.end(), currentNode->connections[i].target) == std::end(closedList))
				{

					float hScore = glm::length(end->position - currentNode->position) / cellSize;
					float gScore = currentNode->gScore + currentNode->connections[i].cost;
					float fScore = hScore + gScore;

					if (std::find(openList.begin(), openList.end(), currentNode->connections[i].target) != std::end(openList))
					{
						//Node is already in the open list with a valid score 
						//so we need to compare the clculated score with the existing score 
						//to find the shorter path

						if (gScore < currentNode->connections[i].target->gScore)
						{
							currentNode->connections[i].target->gScore = gScore;
							currentNode->connections[i].target->hScore = hScore;
							currentNode->connections[i].target->fScore = fScore;
							currentNode->connections[i].target->previous = currentNode;
						}

					}
					else {

						currentNode->connections[i].target->gScore = gScore;
						currentNode->connections[i].target->hScore = hScore;
						currentNode->connections[i].target->fScore = fScore;
						currentNode->connections[i].target->previous = currentNode;
						openList.push_back(currentNode->connections[i].target);
					}
				}
			}
		}

		currentNode = end;
		while (currentNode != nullptr) {
			path.push_back(currentNode);
			currentNode = currentNode->previous;
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	void NodeMap::DrawPath()
	{
		if (path.empty()) return;
		for (int i = 1; i < path.size(); i++) {
			DrawLine(path[i]->position.x, path[i]->position.y, path[i - 1]->position.x, path[i - 1]->position.y, BLACK);
		}
	}

	Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
	{
		int i = (int)(worldPos.x / cellSize);
		if (i < 0 || i >= width) return nullptr;

		int j = (int)(worldPos.y) / cellSize;
		if (j < 0 || j >= height) return nullptr;

		return GetNode(i, j);
	}

	float NodeMap::GetCellSize()
	{
		return cellSize;
	}

	NodeMap::~NodeMap()
	{
		for (int i = 0; i < (width * height); i++) {
			if (nodes[i] != nullptr) {
				delete nodes[i];
			}
		}
		delete[] nodes;
	}

	Node::Node(float x, float y)
	{
		position.x = x;
		position.y = y;
	}


	void Node::ConnectTo(Node* other, float cost)
	{
		connections.push_back(Edge(other, cost));
	}

	Edge::Edge() : Edge(nullptr, 0)
	{
	}

	Edge::Edge(Node* target, float cost) : target{ target }, cost{ cost }
	{
	}
}