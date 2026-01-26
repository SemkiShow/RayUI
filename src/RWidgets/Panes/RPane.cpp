// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Panes/RPane.hpp"

void RPane::Draw()
{
    rui::DrawRectangleBorder(bounds, drawBorder, borderThickness, color, *theme, themeState);
    DrawCentralWidget();
}
