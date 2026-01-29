// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RTextboxInt.hpp"
#include "RCore/Api.hpp"

void RTextboxInt::Update()
{
    RWidget::Update();
    RTextbox::CheckEditing();

    if (value.size() > 1 && value[0] == '0') value.erase(value.begin());
    if (value.size() > 2 && value[0] == '-' && value[1] == '0') value.erase(value.begin() + 1);

    if (selected)
    {
        int key = rui::GetCharPressed();
        while (key > 0)
        {
            // Allow digits
            bool isDigit = (key >= '0' && key <= '9');

            // Allow minus sign ONLY if it's the first character
            bool isMinus = (key == '-' && value.empty());

            if (isDigit || isMinus)
            {
                value += (char)key;
            }

            key = rui::GetCharPressed();
        }

        if (rui::IsKeyPressed(RKey::Backspace))
        {
            Utf8PopBack(value);
        }
    }
}
