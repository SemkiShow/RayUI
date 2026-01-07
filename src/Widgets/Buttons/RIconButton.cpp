// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Buttons/RIconButton.hpp"

void RIconButton::Draw()
{
    RButton::Draw();

    RVector2 iconPos = bounds.GetPosition();
    float iconSize = std::min(bounds.width, bounds.height);
    iconPos.x += (bounds.width - iconSize) / 2;
    rui::DrawIcon(icon, iconPos, iconSize, GetThemeColor(RThemeList::Secondary, themeState));
}
