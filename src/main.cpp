#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raygui_styles/cyber/style_cyber.h>

#include "visualisation.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Algorithms Playground");
    SetTargetFPS(30);
    GuiLoadStyleCyber();
    GuiSetStyle(0, 16, 16);

    int scroll_index = 0;
    int active = 0;
    int current_choice = -1;

    std::vector<std::string> algorithms_list = Visualisation::get_visualisations_list();
    std::string algorithms_list_string = Visualisation::get_visualisations_list_string();
    std::unique_ptr<Visualisation> vis = nullptr;

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_ESCAPE))
            break;
        
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(0, BACKGROUND_COLOR)));
    

        const int LIST_WIDTH = WINDOW_WIDTH * 0.20;
        const int LIST_HEIGHT = WINDOW_HEIGHT;
        GuiListView({ 0, 0, LIST_WIDTH, LIST_HEIGHT }, algorithms_list_string.c_str(), &scroll_index, &active);


        if (active >= 0 && current_choice != active)
        {
            const char* chosen_algo = algorithms_list[active].c_str();

            vis = Visualisation::get_visualisation(chosen_algo);

            current_choice = active;
        }
        else if (active == -1)
            vis = nullptr;

        GuiLabel({ LIST_WIDTH * 1.02, 10, WINDOW_WIDTH - LIST_WIDTH, 30 }, algorithms_list[current_choice].c_str());
        
        if (vis)
        {
            Rectangle visualisation_bounds = {LIST_WIDTH * 1.02,
                                              WINDOW_HEIGHT * 0.10, 
                                              (WINDOW_WIDTH - LIST_WIDTH) * 0.6, 
                                              WINDOW_HEIGHT * 0.8};


            Rectangle control_bounds = {LIST_WIDTH * 1.02 + (WINDOW_WIDTH - LIST_WIDTH) * 0.6,
                                        WINDOW_HEIGHT * 0.10,
                                        (WINDOW_WIDTH - LIST_WIDTH) * 0.4,
                                        WINDOW_HEIGHT * 0.8};

            vis->paint_visualisation(visualisation_bounds, GetFrameTime());
            GuiWindowBox(control_bounds, algorithms_list[current_choice].c_str());
            vis->paint_controls(control_bounds);
        }
        EndDrawing();
    }

    CloseWindow();
}


