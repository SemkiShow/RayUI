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

        SetSize(rui::GetWindowSize());

        if (centralWidget && centralWidget->IsVisible())
        {
            auto centralWidgetBounds = GetBounds();
            centralWidgetBounds = AddMargin(centralWidgetBounds, margin);
            centralWidgetBounds = ClampBounds(centralWidgetBounds, centralWidget->GetMinSize(),
                                              centralWidget->GetMaxSize());
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
