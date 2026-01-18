// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Buttons/RLabelButton.hpp"
#include "Core/Translations.hpp"

void RLabelButton::Draw()
{
    RButton::Draw();

    RRectangle labelBounds = AddMargin(bounds, margin);
    RVector2 labelSize = rui::MeasureText(font, label, labelBounds.height, fontSpacing);
    if (labelHAlign == RAlign::HCenter)
        labelBounds.x += (GetWidth() - 2 * margin - labelSize.x) / 2;
    if (labelHAlign == RAlign::Right) labelBounds.x += (GetWidth() - 2 * margin - labelSize.x);

    rui::DrawText(font, label, labelBounds.GetPosition(), labelBounds.height, fontSpacing,
                  GetThemeColor(RThemeList::Text, themeState));
}

void RLabelButton::UpdateLabels()
{
    label = GetText(labelId);
    UpdateBounds();
}
