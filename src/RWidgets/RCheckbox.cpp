// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RCheckbox.hpp"

void RCheckbox::Update()
{
    RButton::Update();

    if (IsClicked())
    {
        SetValue(!value);
    }
}
