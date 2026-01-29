// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RLabel.hpp"
#include "RCore/Translations.hpp"

void RLabel::Shrink()
{
    RVector2 size = rui::MeasureText(font, label, maxSize.y, fontSpacing);
    SetSize(size);
}

void RLabel::Draw() { rui::DrawText(font, label, GetPosition(), maxSize.y, fontSpacing, color); }

void RLabel::UpdateLabels()
{
    label = GetText(labelId);
    UpdateBounds();
}
