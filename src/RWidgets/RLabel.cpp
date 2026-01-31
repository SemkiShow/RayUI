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

void RLabel::Draw()
{
    auto lines = Split(label, '\n');
    RVector2 size = rui::MeasureText(font, label, maxSize.y, fontSpacing);
    float posY = GetPositionY();
    for (auto& line: lines)
    {
        auto lineSize = rui::MeasureText(font, line, maxSize.y, fontSpacing);
        float posX = GetPositionX();

        switch (alignH)
        {
        case RAlign::Left:
            break;
        case RAlign::HCenter:
            posX += (size.x - lineSize.x) / 2;
            break;
        case RAlign::Right:
            posX += (size.x - lineSize.x);
            break;
        default:
            throw std::runtime_error("Invalid alignH set!");
            break;
        }

        rui::DrawText(font, line, {posX, posY}, maxSize.y, fontSpacing, color);

        posY += lineSize.y;
    }
}

void RLabel::UpdateLabels()
{
    label = GetText(labelId);
    UpdateBounds();
}
