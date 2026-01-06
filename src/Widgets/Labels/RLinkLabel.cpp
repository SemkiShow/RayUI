// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Labels/RLinkLabel.hpp"
#include "Core/Native.hpp"

void RLinkLabel::Update()
{
    RWidget::Update();
    if (IsMouseLeftReleased())
    {
        OpenLink(link);
    }
}
