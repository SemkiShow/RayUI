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
            widget->UpdateBounds();
    }
    for (auto& widget: widgets)
        widget->Update();
}

void RLayout::Draw()
{
    for (auto& widget: widgets)
        widget->Draw();
}
