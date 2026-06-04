#ifndef DUMMY_H
#define DUMMY_H

#include "visualisation.hpp"
#include <string>

class DummyVisualisation : public Visualisation
{
    private:
        std::string str;
        bool enable_textbox = false;
    public:
        void paint_visualisation(Rectangle bounds, float dt) override;
        void paint_controls(Rectangle bounds) override;
        
};


#endif

