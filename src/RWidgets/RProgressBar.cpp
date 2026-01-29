// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RProgressBar.hpp"
#include "RCore/Api.hpp"

void RProgressBar::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);

    RRectangle barBounds = AddMargin(bounds, margin);
    barBounds.width = Map(value, minValue, maxValue, 0, barBounds.width);
    rui::DrawRectangleRounded(barBounds, roundness, segments,
                              GetThemeColor(themeList, RThemeState::Highlighted));

    rui::DrawRectangleRoundedLines(bounds, roundness, segments, borderThickness, color);
}
