// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include <RayUI.hpp>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Vector2 windowSize{16 * 50, 9 * 50};
std::shared_ptr<RApplication> app;

class MainWindow : public RWindow
{
  public:
    MainWindow()
    {
        auto pane = std::make_shared<RPaneRounded>();
        pane->SetMinSize({100, 100});
        SetCentralWidget(pane);

        auto layout = std::make_shared<RVBoxLayout>();
        pane->SetLayout(layout);

        auto link = std::make_shared<RLinkLabel>("https://github.com/SemkiShow/RayUI",
                                                 "https://github.com/SemkiShow/RayUI");
        layout->AddWidget(link);

        auto textBox = std::make_shared<RTextbox>("Enter text...");
        layout->AddWidget(textBox);

        auto textBoxInt = std::make_shared<RTextboxInt>("Enter an int...");
        layout->AddWidget(textBoxInt);

        auto textBoxDouble = std::make_shared<RTextboxDouble>("Enter a double...");
        layout->AddWidget(textBoxDouble);

        auto colorLayout = std::make_shared<RHBoxLayout>();
        colorLayout->SetAlignment(RAlign::Left);
        layout->AddWidget(colorLayout);

        auto label = std::make_shared<RLabel>("label");
        colorLayout->AddWidget(label);

        auto bar = std::make_shared<RBar>();
        bar->SetAlignment(RAlign::VCenter);
        layout->AddWidget(bar);

        auto colorLayout2 = std::make_shared<RHBoxLayout>();
        colorLayout2->SetAlignment(RAlign::HCenter);
        layout->AddWidget(colorLayout2);

        auto bar2 = std::make_shared<RBar>();
        bar2->SetAlignment(RAlign::Bottom);
        layout->AddWidget(bar2);

        auto colorLayout3 = std::make_shared<RHBoxLayout>();
        colorLayout3->SetAlignment(RAlign::Right);
        layout->AddWidget(colorLayout3);

        RColor colors[] = {{255, 0, 0},     {0, 255, 0},   {0, 0, 255},
                           {255, 255, 0},   {255, 0, 255}, {0, 255, 255},
                           {255, 255, 255}, {0, 0, 0},     {127, 127, 127}};

        for (auto& color: colors)
        {
            auto rec = std::make_shared<RPane>(color);
            if (color == RColor{127, 127, 127}) rec->SetVisible(false);
            if (color == RColor{255, 255, 0}) rec->SetAlignment(RAlign::HCenter);
            rec->SetMaxSize({25, 25});
            colorLayout->AddWidget(rec);

            auto rec2 = std::make_shared<RPane>(*rec);
            rec2->SetMaxWidth(rec2->GetMaxWidth() * 3);
            rec2->SetAlignment(RAlign::Left);
            colorLayout2->AddWidget(rec2);

            auto rec3 = std::make_shared<RPane>(*rec2);
            rec3->SetMaxWidth(rec->GetMaxWidth());
            rec3->SetMaxHeight(rec3->GetMaxHeight() * 3);
            colorLayout3->AddWidget(rec3);

            Connect([rec]() { return rec->IsMouseLeftDown(); },
                    [rec]() { std::cout << "Mouse down on " << rec->GetColor() << '\n'; });

            Connect([rec2]() { return rec2->IsMouseLeftPressed(); },
                    [rec2]() { std::cout << "Mouse pressed on " << rec2->GetColor() << '\n'; });

            Connect([rec3]() { return rec3->IsMouseLeftReleased(); },
                    [rec3]() { std::cout << "Mouse released on " << rec3->GetColor() << '\n'; });
        }
    }
};

void InitUI()
{
    app = std::make_shared<RApplication>();

    auto mainWindow = std::make_shared<MainWindow>();
    app->AddWindow(mainWindow);

    // app->SetTheme(std::make_shared<RThemeDark>());
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
