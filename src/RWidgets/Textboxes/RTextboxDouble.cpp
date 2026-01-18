// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Textboxes/RTextboxDouble.hpp"
#include "RCore/Api.hpp"

void RTextboxDouble::Update()
{
    RWidget::Update();
    RTextbox::CheckEditing();

    if (value.size() > 1 && value[0] == '0' && value[1] != '.') value.erase(value.begin());
    if (value.size() > 2 && value[0] == '-' && value[1] == '0' && value[2] != '.')
        value.erase(value.begin() + 1);

    if (selected)
    {
        int key = rui::GetCharPressed();
        while (key > 0)
        {
            bool isDigit = (key >= '0' && key <= '9');
            bool isMinus = (key == '-' && value.empty());

            // Check if it's a dot and if we don't already have one
            bool isDot = (key == '.' && value.find('.') == std::string::npos);

            if (isDigit || isMinus || isDot)
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
