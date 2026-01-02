// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include <RayUI.hpp>
#include <raylib.h>
#include <raymath.h>

Vector2 windowSize{16 * 50, 9 * 50};
std::shared_ptr<RApplication> app;
std::shared_ptr<RWindow> window;
std::shared_ptr<RVBoxLayout> layout;
std::shared_ptr<RPane> pane, rec;

void InitUI()
{
    app = std::make_shared<RApplication>();

    window = std::make_shared<RWindow>();
    window->SetMargin(0);

    layout = std::make_shared<RVBoxLayout>();

    pane = std::make_shared<RPane>();
    pane->SetMinSize({100, 100});
    layout->AddWidget(pane);

    rec = std::make_shared<RPane>();
    rec->SetMaxSize({100, 100});
    layout->AddWidget(rec);

    window->SetCentralWidget(layout);

    app->AddWindow(window);
}

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

    app->Update();
    app->Draw();

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

    InitUI();

    while (!WindowShouldClose())
    {
        DrawFrame();
    }

    CloseWindow();

    return 0;
}
