// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RHBoxLayout.hpp"
#include <cmath>

void RHBoxLayout::ShrinkToContent()
{
    int visibleCount = 0;
    float maxHeight = 0, totalWidth = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            widget->ShrinkToContent();
            visibleCount++;
            maxHeight = fmax(maxHeight, widget->GetWidth());
            totalWidth += widget->GetHeight() + padding;
        }
    }
    totalWidth -= padding;

    SetWidgetPositions();

    RVector2 newSize{2 * margin, maxHeight + 2 * margin};
    if (visibleCount > 0) newSize.x += totalWidth;
    SetSize(newSize);
}

void RHBoxLayout::Update()
{
    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

    updateBounds = false;

    float fixedWidth = 0;
    int visibleCount = 0, dynamicCount = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            if (widget->GetMaxWidth() < 0)
                dynamicCount++;
            else
                fixedWidth += widget->GetMaxWidth();
            visibleCount++;
        }
    }

    if (visibleCount == 0) return;

    float maxHeight = GetHeight() - 2 * margin;
    float dynamicWidth = GetHeight() - 2 * margin - (visibleCount - 1) * padding - fixedWidth;
    dynamicWidth = fmax(0, dynamicWidth);
    if (dynamicCount > 0) dynamicWidth /= dynamicCount;
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
    }

    SetWidgetPositions();

    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->UpdateBounds();
    }

    RLayout::UpdateWidgets();

    ShrinkToContent();
}
