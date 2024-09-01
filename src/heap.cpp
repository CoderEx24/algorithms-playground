#include "heap.hpp"
#include <raylib.h>
#include <raygui.h>
#include <stdexcept>
#include <string>
#include <iostream>

void Heap::heapify()
{
    if (heap.size() <= 1) return;

    for (size_t i = heap.size() - 1; i > 1; i /= 2)
        if (heap[parent(i)] <= heap[i])
            std::swap(heap[parent(i)], heap[i]);
}

void Heap::paint_controls(Rectangle bounds)
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

void Heap::paint_visualisation(Rectangle bounds, float dt)
{
    for (int i = 1; i < heap.size(); i ++)
    {
        DrawRectangle(bounds.x * 1.20f + 40 * i, bounds.y * 1.30f, 40, 40, WHITE);
        DrawText(TextFormat("%i", heap[i]), 6 + bounds.x * 1.20f + 40 * i, 6 + bounds.y * 1.30f, 16, BLACK);
    }


    for (int h = 0; std::pow(2, h) <= heap.size() - 1; h ++)
        for (int i = 0; i < std::pow(2, h); i ++)
        {
            int ball_radius = 60;
            Vector2 base = { bounds.x + bounds.width * 0.50f, bounds.y + bounds.height * 0.30f };
            Vector2 ball = { base.x - (ball_radius * 2.0f) * h + (ball_radius * 3.0f) * i,
                             base.y + (ball_radius * 2.5f) * h };

            int idx = std::pow(2, h) + i;
            if (idx + 1 > heap.size()) break;
            DrawCircle(ball.x, ball.y, ball_radius, WHITE);
            DrawText(TextFormat("h:%i i:%i %i\n%i", h, i, idx, heap[idx]), ball.x + 3, ball.y + 3, 10, BLACK);
        }

    /* for (int level = 0; level < std::floor(std::log2(heap.size())); level++)
        for (int i = std::pow(2, level) - 1; i < std::pow(2, level + 1); i ++)
        {
            int ball_radius = 20;
            Vector2 base = { bounds.x * 2.0f, bounds.y * 2.0f };
            Vector2 ball = { base.x - (ball_radius * 2.90f) * level + (ball_radius * 0.90f) * i, 
                             base.y + (ball_radius * 1.40f) * level };

            DrawCircle(ball.x, ball.y, ball_radius, WHITE);
            DrawText(TextFormat("%i", heap[i]), ball.x + 6, ball.y + 6, 6, BLACK);
        }
        */

}

