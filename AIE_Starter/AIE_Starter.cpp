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
#include "PathAgent.h"

using namespace AIForGames;

Color GetColor(int option)
{
    switch (option)
    {
    case 0:
        return YELLOW;
    case 1:
        return DARKBLUE;
    case 2:
        return RED;
    case 3:
        return PURPLE;
    case 4:
        return LIME;
    case 5:
        return SKYBLUE;
    case 6:
        return ORANGE;
    case 7:
        return DARKGREEN;
    case 9:
        return GREEN;
    case 10:
        return BLUE;
    case 11:
        return DARKPURPLE;
    case 12:
        return GRAY;
    case 13:
        return RAYWHITE;
    case 14:
        return LIGHTGRAY;
    case 15:
        return GOLD;
    case 16:
        return DARKPURPLE;
    case 17:
        return MAGENTA;
    case 18:
        return VIOLET;
    case 19:
        return BEIGE;
    case 20:
        return BROWN;
    case 21:
        return DARKBROWN;
    case 22:
        return MAROON;
    case 23:
        return DARKGRAY;
    }
    
    return PINK;
}


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 3100;
    int screenHeight = 1800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    std::vector<std::string> asciiMap;
    asciiMap.push_back("00000000000000000000000000000000000000000000000000000000000000");
    asciiMap.push_back("01111111111111111111110000000111111111111111111111111111111110");
    asciiMap.push_back("00001000010000001000010000000100000001000000000000000000100000");
    asciiMap.push_back("00001000010000001000010000000111111111111111111111111110100000");
    asciiMap.push_back("00001000010001001000011111111111100000000000000000000011100000");
    asciiMap.push_back("00001000010001001111000000000011111111111111111100000010000000");
    asciiMap.push_back("00001000010001000001111111111111100001000000000100000010000000");
    asciiMap.push_back("01111111110001000001000000000011100001111110000100000010111110");
    asciiMap.push_back("01001000011111111001111111000011111111000100000111111110001000");
    asciiMap.push_back("01001000000000001000000001000011100000000100000111111110001000");
    asciiMap.push_back("01001011111111111111100001000011111000000100000111111110001000");
    asciiMap.push_back("01001000000000000100111111111111101111111111111111111110001000");
    asciiMap.push_back("01001000000000000100000000000011100000001000000100000010001000");
    asciiMap.push_back("01001000000001111111110000000011100000001000000100000011111110");
    asciiMap.push_back("01001000000000000000010000000011111111111111111100000000000100");
    asciiMap.push_back("01001000000000000000011111111111100000000000000100000000000100");
    asciiMap.push_back("01001111111111111111110000000011100000111111111111111111111110");
    asciiMap.push_back("01000000000000000000000000000011100000000000000000000000000010");
    asciiMap.push_back("01000000000000000000000000000011100000000000000000000000000010");
    asciiMap.push_back("01111111111111111111110000000111111101111111111111111111111110");
    asciiMap.push_back("00001000010000001000010000000111100001000000000000000000100000");
    asciiMap.push_back("00001000010000001000010000000111111111111111111111111110100000");
    asciiMap.push_back("00001000010001001000011111111111100000000000000000000011100000");
    asciiMap.push_back("00001000010001001111000000000011111111111111111100000010000000");
    asciiMap.push_back("00001000010001000001111111111111100001000000000100000010000000");
    asciiMap.push_back("01111111110001000001000000000011100001111110000100000010111110");
    asciiMap.push_back("00001000011111111111111111000011111111000100000111111110001000");
    asciiMap.push_back("00001000000000000000000000000001000000000000000000000010001000");
    asciiMap.push_back("00001011111111111111111111111111111111111111111100000010001000");
    asciiMap.push_back("00001000000000000111111111111111111111111111111100000010001000");
    asciiMap.push_back("00001000000000000111111111111111111111111111111100000010001000");
    asciiMap.push_back("00001011111111111111111111111111111111111111111100000011111110");
    asciiMap.push_back("00001000000000000011111111111111111111111111111100000000000100");
    asciiMap.push_back("00001000000000000011111111111111111111111111111100000000000100");
    asciiMap.push_back("00001111111111111111111111111111111111111111111111111111111100");
    asciiMap.push_back("00000000000000000000000000000000000000000000000000000000000000");

    NodeMap nodeMap;
    nodeMap.Intialise(asciiMap, 50);

    Node* start = nodeMap.GetNode(1, 1);

    int numberOfAgents = 300;
    std::vector<PathAgent*> agents;
    for (int i = 0; i < numberOfAgents; i++)
    {
        PathAgent* a = new PathAgent(&nodeMap);
        a->SetNode(start);
        a->SetSpeed(200 + (rand() %53));
        //a->SetColor({ (unsigned char)(256 - a->GetSpeed()),(unsigned char)(256 - a->GetSpeed()),(unsigned char)a->GetSpeed(), 255});
        a->SetColor(GetColor(rand() % 25));
        agents.push_back(a);
    }

    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        /*if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            start = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            agent.GoToNode(start);
        }*/
        
        for (auto agent : agents)
        {
            agent->Update(deltaTime);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        nodeMap.Draw();
        for (auto agent : agents)
        {
            agent->Draw();
        }
        for (auto agent : agents)
        {
            agent->LateDraw();
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}