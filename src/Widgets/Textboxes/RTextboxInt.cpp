// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Textboxes/RTextboxInt.hpp"
#include "Api.hpp"

void RTextboxInt::Update()
{
    RWidget::Update();
    RTextbox::CheckEditing();

    if (text.size() > 1 && text[0] == '0') text.erase(text.begin());
    if (text.size() > 2 && text[0] == '-' && text[1] == '0') text.erase(text.begin() + 1);

    if (isSelected)
    {
        int key = rui::GetCharPressed();
        while (key > 0)
        {
            // Allow digits
            bool isDigit = (key >= '0' && key <= '9');

            // Allow minus sign ONLY if it's the first character
            bool isMinus = (key == '-' && text.empty());

            if (isDigit || isMinus)
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
