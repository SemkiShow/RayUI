// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Textboxes/RTextboxDouble.hpp"
#include "Api.hpp"

void RTextboxDouble::Update()
{
    RWidget::Update();
    RTextbox::CheckEditing();

    if (text.size() > 1 && text[0] == '0' && text[1] != '.') text.erase(text.begin());
    if (text.size() > 2 && text[0] == '-' && text[1] == '0' && text[2] != '.') text.erase(text.begin() + 1);

    if (selected)
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
