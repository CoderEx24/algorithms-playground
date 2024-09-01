#ifndef HEAP_H
#define HEAP_H

#include "visualisation.hpp"

#include <string>
#include <cmath>

class Heap : public Visualisation
{
    private:
        std::vector<int> heap;
        std::string current_entry;

        void heapify();
        size_t right_child(size_t i) { return 2 * i; }
        size_t left_child(size_t i) { return 2 * i + 1; }
        size_t parent(size_t i) { return std::floor(i / 2); }
    public:
        Heap() { heap.push_back(0xffffffff); }
        void paint_visualisation(Rectangle, float) override;
        void paint_controls(Rectangle) override;
};

#endif

