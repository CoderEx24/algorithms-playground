#include <array>
#include <memory>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raygui_styles/cyber/style_cyber.h>

#include "dummy.hpp"
#include "heap.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Algorithms Playground");
    SetTargetFPS(30);
    GuiLoadStyleCyber();
    GuiSetStyle(0, 16, 16);

    int scroll_index = 0;
    int current_choice = 0;

    std::array<std::unique_ptr<Visualisation>, 2> algorithms_list { 
        std::make_unique<DummyVisualisation>(),
        std::make_unique<HeapVisualisation>(),
    };

    std::array algorithms_labels {
        "Dummy",
        "Heap"
    };

    const char* algorithms_list_string = "Dummy;Heap" ;

    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_ESCAPE))
            break;
        
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(0, BACKGROUND_COLOR)));
    

        const int LIST_WIDTH = WINDOW_WIDTH * 0.20;
        const int LIST_HEIGHT = WINDOW_HEIGHT;
        GuiListView({ 0, 0, LIST_WIDTH, LIST_HEIGHT }, algorithms_list_string, &scroll_index, &current_choice);


        GuiLabel({ LIST_WIDTH * 1.02, 10, WINDOW_WIDTH - LIST_WIDTH, 30 }, algorithms_labels[current_choice]);
        
        if (current_choice > -1)
        {
            Rectangle visualisation_bounds = {LIST_WIDTH * 1.02,
                                              WINDOW_HEIGHT * 0.10, 
                                              (WINDOW_WIDTH - LIST_WIDTH) * 0.6, 
                                              WINDOW_HEIGHT * 0.8};


            Rectangle control_bounds = {LIST_WIDTH * 1.02 + (WINDOW_WIDTH - LIST_WIDTH) * 0.6,
                                        WINDOW_HEIGHT * 0.10,
                                        (WINDOW_WIDTH - LIST_WIDTH) * 0.4,
                                        WINDOW_HEIGHT * 0.8};

            algorithms_list[current_choice]->paint_visualisation(visualisation_bounds, GetFrameTime());
            GuiWindowBox(control_bounds, algorithms_labels[current_choice]);
            algorithms_list[current_choice]->paint_controls(control_bounds);
        }
        EndDrawing();
    }

    CloseWindow();
}


