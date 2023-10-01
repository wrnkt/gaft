#include <iostream>
#include <format>

#include "gaft/gaft.hpp"
#include "gaft/session.hpp"
#include "raylib.h"

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "core window example");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update here
        // .......
        // Draw
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawText("This is the main window.", 190, 200, 20, WHITE);
        EndDrawing();
    }

    // Deinitialization
    CloseWindow();

    return 0;
}
