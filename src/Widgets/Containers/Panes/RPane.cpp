// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Containers/Panes/RPane.hpp"

void RPane::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
        if (layout)
        {
            layout->SetBounds(GetBounds());
            layout->UpdateBounds();
        }
    }
    if (layout) layout->Update();
}

void RPane::Draw()
{
    rui::DrawRectangle(bounds, color);
    if (layout) layout->Draw();
}
