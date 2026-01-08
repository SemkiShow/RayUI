// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Panes/RPaneRounded.hpp"
#include "Api.hpp"

void RPaneRounded::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, borderThickness, color, *theme,
                                    themeState);
    RPane::DrawLayout();
}
