// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Containers/Layouts/RHBoxLayout.hpp"

void RHBoxLayout::Update()
{
    if (updateBounds)
    {
        updateBounds = false;

        float fixedWidth = 0;
        for (auto& widget: widgets)
        {
            if (widget->GetMaxHeight() >= 0 && widget->IsVisible())
                fixedWidth += widget->GetMaxWidth();
        }
        float maxHeight = GetHeight() - 2 * margin;
        float dynamicWidth = GetHeight() - 2 * margin - widgets.size() * padding - fixedWidth;
        float posX = GetPositionX() + margin;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            if (widget->GetMaxWidth() < 0)
            {
                widget->SetWidth(dynamicWidth);
            }
            else
            {
                widget->SetWidth(widget->GetMaxWidth());
            }
            widget->SetHeight(maxHeight);
            widget->SetBounds(
                ClampBounds(widget->GetBounds(), widget->GetMinSize(), widget->GetMaxSize()));
            widget->SetPositionX(posX);
            widget->SetPositionY(GetPositionY() + margin);
            posX += widget->GetWidth() + padding;
        }

        for (auto& widget: widgets)
        {
            if (widget->IsVisible()) widget->UpdateBounds();
        }
    }
    RLayout::UpdateWidgets();
}
