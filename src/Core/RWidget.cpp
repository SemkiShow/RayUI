// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/RWidget.hpp"

void RWidget::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
    }
}
