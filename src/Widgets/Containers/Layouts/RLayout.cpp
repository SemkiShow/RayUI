// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Containers/Layouts/RLayout.hpp"

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
