// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Containers/Windows/RWindow.hpp"

void RWindow::Update()
{
    if (updateBounds)
    {
        updateBounds = false;

        SetSize(rui::GetWindowSize());

        if (centralWidget)
        {
            auto centralWidgetBounds = GetBounds();
            centralWidgetBounds = AddMargin(centralWidgetBounds, margin);
            centralWidgetBounds = ClampBounds(centralWidgetBounds, centralWidget->GetMinSize(),
                                              centralWidget->GetMaxSize());
            centralWidget->SetBounds(centralWidgetBounds);
            centralWidget->UpdateBounds();
        }
    }
    if (centralWidget) centralWidget->Update();
}

void RWindow::Draw()
{
    if (centralWidget) centralWidget->Draw();
}
