#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;

        Edge();
        Edge(Node* target, float cost);

    };

    struct Node {
        glm::vec2 position;
        std::vector<Edge> connections;

        Node(float x, float y);
        void ConnectTo(Node* other, float cost);

        float hScore;
        float gScore;
        float fScore;
        Node* previous;

    };

    class NodeMap {
        int width;
        int height;
        float cellSize;

        Node** nodes;
        std::vector<Node*> m_allNodes;
    public:
        std::vector<Node*> path;
        
        int mapSize;
        void Intialise(std::vector <std::string> asciiMap, int cellSize);

        Node* GetNode(int x, int y);
        Node* GetRandomNode();
        void Draw();
        std::vector<Node*> DijkstrasSearch(Node* start, Node* end);
        void DrawPath();
        Node* GetClosestNode(glm::vec2 worldPos);
        float GetCellSize();

        ~NodeMap();
        


    };



}
