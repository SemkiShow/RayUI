// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Buttons/RButton.hpp"
#include "Api.hpp"

void RButton::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRounded(bounds, roundness, segments, color);
    rui::DrawRectangleRoundedLines(bounds, roundness, segments, borderThickness,
                                   GetThemeColor(RThemeList::Border, themeState));
}
