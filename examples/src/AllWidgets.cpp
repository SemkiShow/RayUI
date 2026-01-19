// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include <RayUI.hpp>
#include <iostream>
#include <raylib.h>

#define _(s) (s)

Vector2 windowSize{16 * 50, 9 * 50};
std::shared_ptr<RApplication> app;
std::shared_ptr<RWindow> popupWindow, settingsWindow;
std::shared_ptr<ROkCancelWindow> okCancelWindow;
bool shouldClose = false;

class MainWindow : public RWindow
{
  public:
    MainWindow()
    {
        auto pane = std::make_shared<RPaneRounded>();
        pane->SetMinSize({100, 100});
        SetCentralWidget(pane);

        auto layout = std::make_shared<RVBoxLayout>();
        pane->SetCentralWidget(layout);

        auto link = std::make_shared<RLinkLabel>("https://github.com/SemkiShow/RayUI",
                                                 "https://github.com/SemkiShow/RayUI");
        layout->AddWidget(link);

        auto textBox = std::make_shared<RTextbox>(_("Enter text..."));
        layout->AddWidget(textBox);

        auto textBoxInt = std::make_shared<RTextboxInt>(_("Enter an int..."));
        layout->AddWidget(textBoxInt);

        auto textBoxDouble = std::make_shared<RTextboxDouble>(_("Enter a double..."));
        layout->AddWidget(textBoxDouble);

        auto button = std::make_shared<RLabelButton>(_("Enable debug mode"));
        layout->AddWidget(button);

        Connect([button] { return button->IsClicked(); },
                [button]
                {
                    std::cout << "RLabelButton is clicked!\n";
                    app->SetDebugMode(!app->IsDebugMode());
                    button->SetLabel(app->IsDebugMode() ? _("Disable debug mode")
                                                        : _("Enable debug mode"));
                },
                button);

        auto slider = std::make_shared<RSlider>(0, 0, 20, RSliderType::Rectangle);
        layout->AddWidget(slider);

        auto sliderInt = std::make_shared<RSliderInt>(0, 0, 20);
        layout->AddWidget(sliderInt);

        progressBar = std::make_shared<RProgressBar>(0, 0, 100);
        layout->AddWidget(progressBar);

        auto colorLayout = std::make_shared<RHBoxLayout>();
        colorLayout->SetAlignment(RAlign::Left);
        layout->AddWidget(colorLayout);

        auto label = std::make_shared<RLabel>(_("label"));
        colorLayout->AddWidget(label);

        auto iconButton = std::make_shared<RIconButton>(RIcon::Cpu);
        colorLayout->AddWidget(iconButton);

        Connect([iconButton] { return iconButton->IsClicked(); },
                []
                {
                    std::cout << "RIconButton is clicked!\n";
                    popupWindow->SetVisible(true);
                },
                iconButton);

        auto settingsButton = std::make_shared<RIconButton>(RIcon::Gear);
        colorLayout->AddWidget(settingsButton);

        Connect([settingsButton] { return settingsButton->IsClicked(); },
                [] { settingsWindow->SetVisible(true); }, settingsButton);

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

            Connect([rec] { return rec->IsMouseLeftDown(); },
                    [rec] { std::cout << "Mouse down on " << rec->GetColor() << '\n'; }, rec);

            Connect([rec2] { return rec2->IsMouseLeftPressed(); },
                    [rec2] { std::cout << "Mouse pressed on " << rec2->GetColor() << '\n'; }, rec2);

            Connect([rec3] { return rec3->IsMouseLeftReleased(); }, [rec3]
                    { std::cout << "Mouse released on " << rec3->GetColor() << '\n'; }, rec3);
        }
    }

    void Update() override
    {
        RWindow::Update();

        progressBar->SetValue(progressBar->GetValue() + 5 * GetFrameTime());
        if (progressBar->GetValue() > progressBar->GetMaxValue()) progressBar->SetValue(0);
    }

  protected:
    std::shared_ptr<RProgressBar> progressBar;
};

class PopupWindow : public RPopupWindow
{
  public:
    PopupWindow()
    {
        auto layout = std::make_shared<RVBoxLayout>();
        SetCentralWidget(layout);

        auto label = std::make_shared<RLabel>(
            _("This is a popup window\nYou can drag it by the title bar!"));
        layout->AddWidget(label);

        auto button = std::make_shared<RLabelButton>(_("Show ok cancel window"));
        layout->AddWidget(button);

        Connect([button] { return button->IsClicked(); }, [] { okCancelWindow->SetVisible(true); },
                button);
    }
};

class SettingsWindow : public RPopupWindow
{
  public:
    SettingsWindow()
    {
        auto layout = std::make_shared<RGridLayout>(2);
        SetCentralWidget(layout);

        auto label = std::make_shared<RLabel>(_("label1"));
        layout->AddWidget(label);

        auto label2 = std::make_shared<RLabel>(_("label2"));
        layout->AddWidget(label2);

        auto label3 = std::make_shared<RLabel>(_("label3"));
        layout->AddWidget(label3);

        auto checkbox = std::make_shared<RCheckbox>();
        layout->AddWidget(checkbox);
    }
};

void InitUI()
{
    app = std::make_shared<RApplication>();
    // app->SetLanguage("RayUI", "resources/locales", "pl");

    auto mainWindow = std::make_shared<MainWindow>();
    app->AddWindow(mainWindow);

    popupWindow = std::make_shared<PopupWindow>();
    popupWindow->SetVisible(false);
    app->AddWindow(popupWindow);

    settingsWindow = std::make_shared<SettingsWindow>();
    settingsWindow->SetVisible(false);
    app->AddWindow(settingsWindow);

    okCancelWindow = std::make_shared<ROkCancelWindow>(
        _("Would you like to close the app?\nLine 2\nLine 3"), _("Yes"), _("No"));
    okCancelWindow->SetVisible(false);
    okCancelWindow->Connect([] { return okCancelWindow->IsOkClicked(); },
                            [] { shouldClose = true; }, okCancelWindow);
    app->AddWindow(okCancelWindow);

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

    while (!shouldClose && !WindowShouldClose())
    {
        DrawFrame();
    }

    CloseWindow();

    return 0;
}
