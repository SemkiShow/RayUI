// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Labels/RLabel.hpp"
#include "Api.hpp"

void RLabel::Shrink()
{
    RVector2 size;
    if (font)
        size = rui::MeasureTextFont(*font, text, fontSize, fontSpacing);
    else
        size = rui::MeasureText(text, fontSize);
    SetSize(size);
}

void RLabel::Draw()
{
    if (font)
        rui::DrawTextFont(*font, text, GetPosition(), fontSize, fontSpacing, color);
    else
        rui::DrawText(text, GetPosition(), fontSize, color);
}
