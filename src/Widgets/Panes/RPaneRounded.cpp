// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Panes/RPaneRounded.hpp"
#include "Api.hpp"

void RPaneRounded::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRounded(bounds, roundness, segments, color);
    rui::DrawRectangleRoundedLines(bounds, roundness, segments, borderThickness,
                                   GetThemeColor(RThemeList::Border, themeState));
    RPane::DrawLayout();
}
