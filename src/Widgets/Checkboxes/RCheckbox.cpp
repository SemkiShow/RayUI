// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Checkboxes/RCheckbox.hpp"

void RCheckbox::Update()
{
    RButton::Update();

    if (IsClicked())
    {
        SetValue(!value);
    }
}
