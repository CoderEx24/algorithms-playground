#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <raylib.h>
#include <memory>
#include <vector>

class Visualisation
{
    public:
        static std::string get_visualisations_list_string();
        static std::vector<std::string> get_visualisations_list();
        static std::unique_ptr<Visualisation> get_visualisation(const char*);
        virtual void paint_visualisation(Rectangle, float) = 0;
        virtual void paint_controls(Rectangle) = 0;
        virtual ~Visualisation() = default;
};

#endif
