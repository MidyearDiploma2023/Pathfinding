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

        float gScore;
        Node* previous;

    };

    class NodeMap {
        int width;
        int height;
        float cellSize;

        Node** nodes;
        std::vector<Node*> path;

    public:
        int mapSize;
        void Intialise(std::vector <std::string> asciiMap, int cellSize);

        Node* GetNode(int x, int y);

        void Draw();

        std::vector<Node*> DijkstrasSearch(Node* start, Node* end);

        void DrawPath();

        ~NodeMap();
        


    };



}
