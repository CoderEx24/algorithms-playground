#include "visualisation.hpp"
#include <numeric>
#include <sstream>
#include <vector>

#include <raygui.h>

class DummyVisualisation : public Visualisation
{
    private:
        std::string str;
        bool enable_textbox = false;
    public:
        void paint_visualisation(Rectangle bounds, float dt) override
        {
            DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, 
                    WHITE);
            DrawText("This is a dummy visualisation\nChoose something from\nthe list on the left",
                    bounds.x + 12, bounds.y + 12, 20, BLACK);

            DrawText(TextFormat("Entered: %s", str.c_str()), bounds.x * 1.01f, bounds.y * 2.50f, 20, RED); 
        }

        void paint_controls(Rectangle bounds) override
        {
            GuiWindowBox(bounds, "Dummy Controls");
            GuiToggle({ bounds.x * 1.30f, bounds.y * 1.40f,
                        80, 30 }, "Enable", &enable_textbox);
            GuiTextBox({ bounds.x * 1.01f, bounds.y * 1.40f,
                         bounds.width * 0.60f, 30}, str.data(), 30, enable_textbox);
        }
};

std::vector<std::string> Visualisation::get_visualisations_list()
{
    std::vector<std::string> algorithms;
    // {{{ algorithm list
    algorithms.push_back("Dummy");
    // }}}

    return algorithms;
}

std::string Visualisation::get_visualisations_list_string()
{
    std::vector<std::string> algorithms = Visualisation::get_visualisations_list();

    std::string result = std::accumulate(algorithms.begin(), algorithms.end(), std::string(), [](auto acc, auto i) {
            std::stringstream s;
            s << acc << i << ";";
            return s.str();
    });

    result.pop_back();
    return result;
}

std::unique_ptr<Visualisation> Visualisation::get_visualisation(const char* choice)
{
    return std::make_unique<DummyVisualisation>();
}

