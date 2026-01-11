// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Buttons/RButton.hpp"
#include "Core/Api.hpp"

void RButton::Update()
{
    if (wasSelected) wasSelected = false;
    if (IsMouseLeftPressed())
    {
        selected = true;
    }
    if (rui::IsMouseButtonReleased(RMouseButton::Left))
    {
        if (selected) wasSelected = true;
        selected = false;
    }
    RWidget::Update();
}

void RButton::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, borderThickness, color, *theme,
                                    themeState);
}
