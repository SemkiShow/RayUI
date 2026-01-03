// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include <RayUI.hpp>
#include <raylib.h>
#include <raymath.h>

Vector2 windowSize{16 * 50, 9 * 50};
std::shared_ptr<RApplication> app;

void InitUI()
{
    app = std::make_shared<RApplication>();

    auto window = std::make_shared<RWindow>();

    auto pane = std::make_shared<RPaneRounded>();
    pane->SetMinSize({100, 100});

    auto layout = std::make_shared<RVBoxLayout>();
    pane->SetLayout(layout);

    auto colorLayout = std::make_shared<RHBoxLayout>();
    RColor colors[] = {{255, 0, 0},   {0, 255, 0},   {0, 0, 255},
                       {255, 255, 0}, {255, 0, 255}, {0, 255, 255}};
    for (auto& color: colors)
    {
        auto rec = std::make_shared<RPane>(color);
        if (color == RColor{255, 0, 0}) rec->SetVisible(false);
        rec->SetMaxSize({25, 25});
        colorLayout->AddWidget(rec);
    }
    layout->AddWidget(colorLayout);

    window->SetCentralWidget(pane);

    app->AddWindow(window);
}

void DrawFrame()
{
    BeginDrawing();

    ClearBackground(BLACK);

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
