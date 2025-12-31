// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RayUI.hpp"
#include <raylib.h>
#include <raymath.h>

Vector2 windowSize{16 * 50, 9 * 50};

void UpdateWindowSize()
{
    windowSize = {(float)GetRenderWidth(), (float)GetRenderHeight()};
    windowSize /= GetWindowScaleDPI();
}

void DrawFrame()
{
    BeginDrawing();

    ClearBackground(BLACK);

    UpdateWindowSize();

    /* UI stuff */

    EndDrawing();
}

int main()
{
    int flags = 0;
    flags |= FLAG_VSYNC_HINT;
    flags |= FLAG_WINDOW_HIGHDPI;
    flags |= FLAG_WINDOW_RESIZABLE;
    SetConfigFlags(flags);

    InitWindow(windowSize.x, windowSize.y, "RayUI All Widgets Example");

    while (!WindowShouldClose())
    {
        DrawFrame();
    }

    CloseWindow();

    return 0;
}
