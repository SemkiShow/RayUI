// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Windows/RWindow.hpp"

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
}

void RWindow::Draw() { DrawCentralWidget(); }
