#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raygui_styles/cyber/style_cyber.h>

#define WINDOW_SIDELENGTH 800

int main()
{
    InitWindow(WINDOW_SIDELENGTH, WINDOW_SIDELENGTH, "Algorithms Playground");
    SetTargetFPS(30);
    GuiLoadStyleCyber();
    GuiSetStyle(0, 16, 16);

    int scroll_index = 0;
    int active = 0;

    std::vector<std::string> algos(0);
    algos.push_back("algo1");
    algos.push_back("sdiufsdfalgo2");
    algos.push_back("algo3");
    algos.push_back("algo4");
    algos.push_back("algo5");
    algos.push_back("algo6");
    algos.push_back("algo7");
    algos.push_back("algo8");
    algos.push_back("algo9");

    auto algos_string = std::accumulate(algos.begin(), algos.end(), std::string(), [](auto i, auto b) { 
            std::stringstream s;
            s << i << b << ";";
            return s.str();
    });

    algos_string.pop_back();

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_ESCAPE))
            break;
        
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(0, BACKGROUND_COLOR)));
    

        const int LIST_WIDTH = WINDOW_SIDELENGTH * 0.20;
        const int LIST_HEIGHT = WINDOW_SIDELENGTH;
        GuiListView({ 0, 0, LIST_WIDTH, LIST_HEIGHT }, algos_string.c_str(), &scroll_index, &active);


        /* GuiListView({ 0, 0, LIST_WIDTH, LIST_HEIGHT }, "Algorithms;"
                                         "Algorithm2", &scroll_index, &active); */

        GuiLabel({ LIST_WIDTH * 1.02, 10, WINDOW_SIDELENGTH - LIST_WIDTH, 30 }, algos[active].c_str());
            
        EndDrawing();
    }

    CloseWindow();
}


