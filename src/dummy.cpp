#include "dummy.hpp"

#include <raygui.h>

void DummyVisualisation::paint_visualisation(Rectangle bounds, float dt)
{
    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, 
            WHITE);
    DrawText("This is a dummy visualisation\nChoose something from\nthe list on the left",
            bounds.x + 12, bounds.y + 12, 20, BLACK);

    DrawText(TextFormat("Entered: %s", str.c_str()), bounds.x * 1.01f, bounds.y * 2.50f, 20, RED); 
}

void DummyVisualisation::paint_controls(Rectangle bounds)
{
    GuiToggle({ bounds.x * 1.30f, bounds.y * 1.40f,
                80, 30 }, "Enable", &enable_textbox);
    GuiTextBox({ bounds.x * 1.01f, bounds.y * 1.40f,
                 bounds.width * 0.60f, 30}, str.data(), 30, enable_textbox);
}
