// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RPaneRounded.hpp"

void RPaneRounded::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, drawBorder, borderThickness, color,
                                    *theme, themeState);
    RPane::DrawCentralWidget();
}
