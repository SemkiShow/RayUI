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
            maxHeight = std::max(maxHeight, widget->GetHeight());
            totalWidth += widget->GetWidth() + padding;
        }
    }
    totalWidth -= padding;

    float posX = GetPositionX() + margin, widthLeft = totalWidth;
    for (auto& widget: widgets)
    {
        float delta = widget->GetWidth() + padding;
        switch (widget->GetAlignH())
        {
        case RAlign::Left:
            break;
        case RAlign::HCenter:
            posX =
                std::max(posX, GetPositionX() + margin + (GetWidth() - 2 * margin - widthLeft) / 2);
            break;
        case RAlign::Right:
            posX = std::max(posX, GetPositionX() + margin + (GetWidth() - 2 * margin - widthLeft));
            break;
        default:
            throw std::runtime_error("Invalid alignH set!");
            break;
        }
        widget->SetPositionX(posX);
        posX += delta;
        widthLeft -= delta;

        switch (widget->GetAlignV())
        {
        case RAlign::Top:
            widget->SetPositionY(GetPositionY() + margin);
            break;
        case RAlign::VCenter:
            widget->SetPositionY(GetPositionY() + margin +
                                 (GetHeight() - 2 * margin - widget->GetHeight()) / 2);
            break;
        case RAlign::Bottom:
            widget->SetPositionY(GetPositionY() + margin +
                                 (GetHeight() - 2 * margin - widget->GetHeight()));
            break;
        default:
            throw std::runtime_error("Invalid alignV set!");
            break;
        }

        widget->UpdateBounds();
        widget->Update();
    }

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

    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->UpdateBounds();
    }

    RLayout::UpdateWidgets();

    ShrinkToContent();
}
