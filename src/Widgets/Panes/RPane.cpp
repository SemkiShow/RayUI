// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Panes/RPane.hpp"

void RPane::ResetEvents()
{
    if (layout) layout->ResetEvents();
    RWidget::ResetEvents();
}

bool RPane::PollEvents()
{
    if (PollLayoutEvents()) return true;
    return RWidget::PollEvents();
}

void RPane::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
        if (layout && layout->IsVisible())
        {
            layout->SetBounds(GetBounds());
            layout->UpdateBounds();
        }
    }
    if (layout && layout->IsVisible()) layout->Update();
}

void RPane::Draw()
{
    rui::DrawRectangle(bounds, color);
    DrawLayout();
}
