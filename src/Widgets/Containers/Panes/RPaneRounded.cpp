// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Widgets/Containers/Panes/RPaneRounded.hpp"

void RPaneRounded::Draw()
{
    rui::DrawRectangleRounded(bounds, roundness, segments, color);
    RPane::DrawLayout();
}
