// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Labels/RLabel.hpp"
#include "Api.hpp"

void RLabel::Shrink()
{
    RVector2 size;
    if (font)
        size = rui::MeasureTextFont(*font, text, maxSize.y, fontSpacing);
    else
        size = rui::MeasureText(text, maxSize.y);
    SetSize(size);
}

void RLabel::Draw()
{
    if (font)
        rui::DrawTextFont(*font, text, GetPosition(), maxSize.y, fontSpacing, color);
    else
        rui::DrawText(text, GetPosition(), maxSize.y, color);
}
