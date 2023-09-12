/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000");
    asciiMap.push_back("0101110111100");
    asciiMap.push_back("0101011101110");
    asciiMap.push_back("0101000000000");
    asciiMap.push_back("0101111111110");
    asciiMap.push_back("0100000010000");
    asciiMap.push_back("0111111111110");
    asciiMap.push_back("0000000000000");

    NodeMap nodeMap;
    nodeMap.Intialise(asciiMap, 50);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(11, 2);
    nodeMap.path = nodeMap.DijkstrasSearch(start, end);

    //std::vector<Node*> path = nodeMap.DijkstrasSearch(nodeMap.GetNode(1, 1), nodeMap.GetNode(1, 3));


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            start = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMap.path = nodeMap.DijkstrasSearch(start, end);
        }
        if (IsMouseButtonPressed(1)) {
            Vector2 mousePos = GetMousePosition();
            end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMap.path = nodeMap.DijkstrasSearch(start, end);
        }
        


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        nodeMap.Draw();
        nodeMap.DrawPath();

       

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}