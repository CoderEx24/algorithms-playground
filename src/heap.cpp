#include "heap.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include <raygui.h>

void HeapVisualisation::heapify()
{
    if (heap.size() <= 1) return;

    for (size_t i = heap.size() - 1; i > 1; i /= 2)
        if (heap[parent(i)] <= heap[i])
            std::swap(heap[parent(i)], heap[i]);
}

Vector2 HeapVisualisation::calculate_node_coords(Rectangle tree_bounds, size_t node_index)
{
    const int LEVEL_HEIGHT = 30;

    if (node_index == 1) return { tree_bounds.x + tree_bounds.width / 2, tree_bounds.y + LEVEL_HEIGHT };

    Vector2 node_coords = { tree_bounds.x,  tree_bounds.y };
    int N = (int) heap.size() - 1;
    int h_of_node = 0;
    int i = 1;
    for (; i <= node_index; i *= 2, h_of_node ++);
    i /= 2;

    int index_in_column = node_index - i; 

    if (index_in_column == 0)
        node_coords.x += tree_bounds.width / i / 2;
    else if (index_in_column == i - 1)
        node_coords.x += tree_bounds.width - tree_bounds.width / i / 2;
    else
        node_coords.x += (tree_bounds.width / i / 2) + (index_in_column) * (tree_bounds.width / i);

    node_coords.y += LEVEL_HEIGHT * (h_of_node + .5f);

    return node_coords;
}

void HeapVisualisation::paint_controls(Rectangle bounds)
{
    Rectangle textbox = { bounds.x * 1.01f, bounds.y * 1.40f,
                          bounds.width * 0.8f, 30 };
    GuiTextBox(textbox, current_entry.data(), 20, true);

    Rectangle push_button = { textbox.x, textbox.y + textbox.height,
                              bounds.width * 0.40f, 30 };
    if (GuiButton(push_button, "Push"))
    {
        try
        {
            int number = std::stoi(current_entry);
            heap.push_back(number);
            heapify();
        }
        catch (std::invalid_argument e)
        {
        }

        current_entry = "";
        
        for (auto elem : heap)
            std::cout << elem << ", ";
        std::cout << '\n';
    }

    Rectangle pop_button = { push_button.x + push_button.width, push_button.y,
                             push_button.width, 30 };

    if (GuiButton(pop_button, "Pop") && heap.size() > 1)
    {
        heap.pop_back();
        heapify();
    }
}

void HeapVisualisation::paint_visualisation(Rectangle bounds, float dt)
{
    DrawRectangleLinesEx(bounds, 1, PINK);
    Rectangle tree_bounds = { bounds.x,
        bounds.y + bounds.height * .2f, 
        bounds.width, 
        bounds.height * .8f };

    DrawRectangleLinesEx(tree_bounds, 4, GREEN);
    for (int i = 1; i < heap.size(); i ++)
    {
        Vector2 node_coords = calculate_node_coords(tree_bounds, i);

        DrawCircle(node_coords.x, node_coords.y, 10, WHITE);
        DrawText(TextFormat("%d", heap[i]), node_coords.x, node_coords.y, 7, BLACK);
    }

}

