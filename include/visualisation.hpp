#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <raylib.h>

class Visualisation
{
    public:
        virtual void paint_visualisation(Rectangle, float) = 0;
        virtual void paint_controls(Rectangle) = 0;
        virtual ~Visualisation() = default;
};

#endif
