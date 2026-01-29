// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RLinkLabel.hpp"
#include "RCore/Native.hpp"

void RLinkLabel::Update()
{
    RWidget::Update();
    if (IsMouseLeftReleased())
    {
        OpenLink(link);
    }
}
