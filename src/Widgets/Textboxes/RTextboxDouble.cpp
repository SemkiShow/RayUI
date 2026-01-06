// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Textboxes/RTextboxDouble.hpp"
#include "Api.hpp"

void RTextboxDouble::Update()
{
    RWidget::Update();
    RTextbox::CheckEditing();

    if (isSelected)
    {
        int key = rui::GetCharPressed();
        while (key > 0)
        {
            bool isDigit = (key >= '0' && key <= '9');
            bool isMinus = (key == '-' && text.empty());

            // Check if it's a dot and if we don't already have one
            bool isDot = (key == '.' && text.find('.') == std::string::npos);

            if (isDigit || isMinus || isDot)
            {
                text += (char)key;
            }

            key = rui::GetCharPressed();
        }

        if (rui::IsKeyPressed(RKey::Backspace))
        {
            Utf8PopBack(text);
        }
    }
}
