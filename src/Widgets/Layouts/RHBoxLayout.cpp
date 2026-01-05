// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RHBoxLayout.hpp"
#include <cmath>

void RHBoxLayout::Shrink()
{
    float maxHeight = 0, totalWidth = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            widget->Shrink();
            maxHeight = std::max(maxHeight, widget->GetHeight() + 2 * margin);
            totalWidth += widget->GetWidth() + padding;
        }
    }
    totalWidth -= padding;

    bool foundFirstCenter = false;
    float centerWidth = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetAlignH() == RAlign::HCenter) foundFirstCenter = true;
        if (widget->GetAlignH() == RAlign::Right) break;
        if (!foundFirstCenter) continue;

        centerWidth += widget->GetWidth() + padding;
    }
    centerWidth -= padding;

    float posX = GetPositionX() + margin, widthLeft = totalWidth;
    switch (GetAlignH())
    {
    case RAlign::Left:
        break;
    case RAlign::HCenter:
        posX += (GetWidth() - 2 * margin - totalWidth) / 2;
        break;
    case RAlign::Right:
        posX += (GetWidth() - 2 * margin - totalWidth);
        break;
    default:
        throw std::runtime_error("Invalid alignH set!");
        break;
    }

    for (auto& widget: widgets)
    {
        float delta = widget->GetWidth() + padding;
        switch (widget->GetAlignH())
        {
        case RAlign::Left:
            break;
        case RAlign::HCenter:
            posX = std::max(posX,
                            GetPositionX() + margin + (GetWidth() - 2 * margin - centerWidth) / 2);
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

    SetHeight(maxHeight + 2 * margin);
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
    float dynamicWidth = GetWidth() - 2 * margin - (visibleCount - 1) * padding - fixedWidth;
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

    Shrink();
}
