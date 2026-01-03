// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/RWidget.hpp"

bool RWidget::PollEvents() { return false; }

void RWidget::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
    }
}
