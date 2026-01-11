// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Textboxes/RTextbox.hpp"
#include "Core/Api.hpp"
#include "Core/Translations.hpp"

void RTextbox::CheckEditing()
{
    auto beginEditing = [this]()
    {
        selected = true;
        highlighted = true;
    };

    auto stopEditing = [this]()
    {
        selected = false;
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

    if (selected)
    {
        value += GetCharsPressed();
        if (rui::IsKeyPressed(RKey::Backspace))
        {
            Utf8PopBack(value);
        }
    }
}

void RTextbox::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, borderThickness, color, *theme,
                                    themeState);

    RRectangle textBounds = bounds;
    textBounds = AddMargin(textBounds, margin);
    rui::BeginScissorMode(textBounds);
    if (value.empty() && !selected)
    {
        rui::DrawText(font, promptText, textBounds.GetPosition(), textBounds.height, fontSpacing,
                      GetThemeColor(RThemeList::Text, RThemeState::Disabled));
    }
    else
    {
        RVector2 textSize = rui::MeasureText(font, value, textBounds.height, fontSpacing);
        RVector2 pos = textBounds.GetPosition();
        if (textSize.x > textBounds.width) pos.x += textBounds.width - textSize.x;
        rui::DrawText(font, value, pos, textBounds.height, fontSpacing,
                      GetThemeColor(RThemeList::Text, RThemeState::Default));
    }
    rui::EndScissorMode();
}

void RTextbox::UpdateLabels() { promptText = _(promptTextId); }
