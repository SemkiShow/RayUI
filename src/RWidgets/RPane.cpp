// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RPane.hpp"

void RPane::Draw()
{
    rui::DrawRectangleBorder(bounds, drawBorder, borderThickness, color, *theme, themeState);
    DrawCentralWidget();
}
