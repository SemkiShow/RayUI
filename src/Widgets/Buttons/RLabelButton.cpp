// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Buttons/RLabelButton.hpp"
#include "Api.hpp"

void RLabelButton::Draw()
{
    RButton::Draw();

    RRectangle labelBounds = AddMargin(bounds, margin);
    if (font)
    {
        RVector2 labelSize = rui::MeasureTextFont(*font, label, labelBounds.height, fontSpacing);
        if (labelHAlign == RAlign::HCenter) labelBounds.x += (GetWidth() - 2 * margin - labelSize.x) / 2;
        if (labelHAlign == RAlign::Right) labelBounds.x += (GetWidth() - 2 * margin - labelSize.x);
        
        rui::DrawTextFont(*font, label, labelBounds.GetPosition(), labelBounds.height, fontSpacing,
                          GetThemeColor(RThemeList::Text, themeState));
    }
    else
    {
        RVector2 labelSize = rui::MeasureText(label, labelBounds.height);
        if (labelHAlign == RAlign::HCenter) labelBounds.x += (GetWidth() - 2 * margin - labelSize.x) / 2;
        if (labelHAlign == RAlign::Right) labelBounds.x += (GetWidth() - 2 * margin - labelSize.x);

        rui::DrawText(label, labelBounds.GetPosition(), labelBounds.height,
                      GetThemeColor(RThemeList::Text, themeState));
    }
}
