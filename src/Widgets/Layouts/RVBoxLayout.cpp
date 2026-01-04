// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RVBoxLayout.hpp"
#include <cmath>

void RVBoxLayout::Update()
{
    if (updateBounds)
    {
        updateBounds = false;

        float fixedHeight = 0;
        int visibleCount = 0, dynamicCount = 0;
        for (auto& widget: widgets)
        {
            if (widget->IsVisible())
            {
                if (widget->GetMaxHeight() < 0)
                    dynamicCount++;
                else
                    fixedHeight += widget->GetMaxHeight();
                visibleCount++;
            }
        }

        if (visibleCount == 0) return;

        float maxWidth = GetWidth() - 2 * margin;
        float dynamicHeight = GetHeight() - 2 * margin - (visibleCount - 1) * padding - fixedHeight;
        dynamicHeight = fmax(0, dynamicHeight);
        if (dynamicCount > 0) dynamicHeight /= dynamicCount;
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
