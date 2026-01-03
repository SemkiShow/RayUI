// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Containers/Layouts/RLayout.hpp"

bool RLayout::PollEvents()
{
    if (PollWidgetsEvents()) return true;
    return RWidget::PollEvents();
}

void RLayout::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
        for (auto& widget: widgets)
        {
            if (widget->IsVisible()) widget->UpdateBounds();
        }
    }
    UpdateWidgets();
}

void RLayout::Draw()
{
    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->Draw();
    }
}
