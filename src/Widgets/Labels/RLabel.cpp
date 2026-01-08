// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Labels/RLabel.hpp"
#include "Api.hpp"

void RLabel::Shrink()
{
    RVector2 size = rui::MeasureText(font, text, maxSize.y, fontSpacing);
    SetSize(size);
}

void RLabel::Draw() { rui::DrawText(font, text, GetPosition(), maxSize.y, fontSpacing, color); }
