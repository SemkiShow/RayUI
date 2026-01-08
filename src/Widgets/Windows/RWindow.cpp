// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Windows/RWindow.hpp"
#include "Api.hpp"

void RWindow::ResetEvents()
{
    if (centralWidget) centralWidget->ResetEvents();
    RWidget::ResetEvents();
}

bool RWindow::PollEvents()
{
    if (PollCentralWidgetEvents()) return true;
    return RWidget::PollEvents();
}

void RWindow::Update()
{
    if (updateBounds)
    {
        updateBounds = false;

        auto windowSize = rui::GetWindowSize();
        SetSize(GetMaxSize());
        if (maxSize.x < 0) SetWidth(windowSize.x);
        if (maxSize.y < 0) SetHeight(windowSize.y);
        bounds = ClampBounds(bounds, minSize, maxSize);

        if (centralWidget && centralWidget->IsVisible())
        {
            auto centralWidgetBounds = GetBounds();
            centralWidgetBounds = AddMargin(centralWidgetBounds, margin);
            centralWidget->SetBounds(centralWidgetBounds);
            centralWidget->UpdateBounds();
        }
    }
    if (centralWidget && centralWidget->IsVisible()) centralWidget->Update();

    for (auto& [event, func]: events)
    {
        if (event()) func();
    }
}

void RWindow::Draw() { DrawCentralWidget(); }

void RWindow::SetFont(std::shared_ptr<RFont> font)
{
    if (centralWidget) centralWidget->SetFont(font);
    RWidget::SetFont(font);
}

void RWindow::SetTheme(std::shared_ptr<RTheme> theme)
{
    if (centralWidget) centralWidget->SetTheme(theme);
    RWidget::SetTheme(theme);
}

void RWindow::SetScale(float scale)
{
    if (centralWidget) centralWidget->SetScale(scale);
    float delta = scale / this->scale;
    margin *= delta;
    RWidget::SetScale(scale);
}
