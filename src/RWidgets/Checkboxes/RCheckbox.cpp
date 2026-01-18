// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Checkboxes/RCheckbox.hpp"

void RCheckbox::Update()
{
    RButton::Update();

    if (IsClicked())
    {
        SetValue(!value);
    }
}
