// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Textboxes/RTextbox.hpp"
#include "Api.hpp"

void RTextbox::CheckEditing()
{
    auto beginEditing = [this]()
    {
        isSelected = true;
        highlighted = true;
    };

    auto stopEditing = [this]()
    {
        isSelected = false;
        highlighted = false;
        finishedEditing = true;
    };

    if (finishedEditing) finishedEditing = false;
    if (IsMouseLeftReleased()) beginEditing();
    if (!IsMouseHovered() && rui::IsMouseButtonReleased(RMouseButton::Left)) stopEditing();
    if (rui::IsKeyPressed(RKey::Enter)) stopEditing();
}

void RTextbox::Update()
{
    RWidget::Update();
    CheckEditing();

    if (isSelected)
    {
        text += GetCharsPressed();
        if (rui::IsKeyPressed(RKey::Backspace))
        {
            Utf8PopBack(text);
        }
    }
}

void RTextbox::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRounded(bounds, roundness, segments, color);
    rui::DrawRectangleRoundedLines(bounds, roundness, segments, borderThickness, color);

    RRectangle textBounds = bounds;
    textBounds = AddMargin(textBounds, margin);
    rui::BeginScissorMode(textBounds);
    if (font)
    {
        if (text.empty() && !isSelected)
        {
            rui::DrawTextFont(*font, promptText, textBounds.GetPosition(), textBounds.height,
                              fontSpacing, GetThemeColor(RThemeList::Text, RThemeState::Disabled));
        }
        else
        {
            RVector2 textSize = rui::MeasureTextFont(*font, text, textBounds.height, fontSpacing);
            RVector2 pos = textBounds.GetPosition();
            if (textSize.x > textBounds.width) pos.x += textBounds.width - textSize.x;
            rui::DrawTextFont(*font, text, pos, textBounds.height, fontSpacing,
                              GetThemeColor(RThemeList::Text, RThemeState::Default));
        }
    }
    else
    {
        if (text.empty() && !isSelected)
        {
            rui::DrawText(promptText, textBounds.GetPosition(), textBounds.height,
                          GetThemeColor(RThemeList::Text, RThemeState::Disabled));
        }
        else
        {
            RVector2 textSize = rui::MeasureText(text, textBounds.height);
            RVector2 pos = textBounds.GetPosition();
            if (textSize.x > textBounds.width) pos.x += textBounds.width - textSize.x;
            rui::DrawText(text, pos, textBounds.height,
                          GetThemeColor(RThemeList::Text, RThemeState::Default));
        }
    }
    rui::EndScissorMode();
}
