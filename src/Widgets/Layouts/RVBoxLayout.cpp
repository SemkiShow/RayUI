// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RVBoxLayout.hpp"

void RVBoxLayout::Update()
{
    if (updateBounds)
    {
        updateBounds = false;

        float fixedHeight = 0;
        for (auto& widget: widgets)
        {
            if (widget->GetMaxHeight() >= 0 && widget->IsVisible())
                fixedHeight += widget->GetMaxHeight();
        }
        float maxWidth = GetWidth() - 2 * margin;
        float dynamicHeight = GetHeight() - 2 * margin - widgets.size() * padding - fixedHeight;
        float posY = GetPositionY() + margin;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            if (widget->GetMaxHeight() < 0)
            {
                widget->SetHeight(dynamicHeight);
            }
            else
            {
                widget->SetHeight(widget->GetMaxHeight());
            }
            widget->SetWidth(maxWidth);
            widget->SetBounds(
                ClampBounds(widget->GetBounds(), widget->GetMinSize(), widget->GetMaxSize()));
            widget->SetPositionX(GetPositionX() + margin);
            widget->SetPositionY(posY);
            posY += widget->GetHeight() + padding;
        }

        for (auto& widget: widgets)
        {
            if (widget->IsVisible()) widget->UpdateBounds();
        }
    }
    RLayout::UpdateWidgets();
}
