// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Panes/RPaneRounded.hpp"

void RPaneRounded::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRounded(bounds, roundness, segments, color);
    RPane::DrawLayout();
}
