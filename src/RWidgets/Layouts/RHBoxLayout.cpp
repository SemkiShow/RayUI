// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Layouts/RHBoxLayout.hpp"

void RHBoxLayout::Shrink()
{
    // Calculate shrinked size
    float newHeight = 0, totalWidth = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        newHeight = std::max(newHeight, widget->GetHeight() + 2 * margin);
        totalWidth += widget->GetWidth() + padding;
    }
    totalWidth -= padding;

    // Calculate center widgets' width
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

    // Calculate posX offset
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

    // Set widgets' positions
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

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

    // Set shrinked size
    bool allTop = true;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetAlignV() != RAlign::Top)
        {
            allTop = false;
            break;
        }
    }
    SetWidth(posX - bounds.x - padding + margin);
    if (allTop)
        SetHeight(newHeight + margin);
    else
        SetHeight(std::max(bounds.height, newHeight + margin));
    bounds = ClampBounds(bounds, minSize, maxSize);
}

void RHBoxLayout::Update()
{
    CleanupWidgets();

    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

    updateBounds = false;

    // Calculate widths
    int visibleCount = 0, dynamicCount = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetMaxWidth() < 0) dynamicCount++;
        visibleCount++;
    }
    float dynamicWidth = GetWidth() - 2 * margin - (visibleCount - 1) * padding;

    if (visibleCount == 0) return;

    // Update widgets' bounds upfront
    for (auto& widget: widgets)
    {
        widget->UpdateBounds();
    }

    // Set widgets' sizes
    float maxHeight = GetHeight() - 2 * margin;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetMaxWidth() < 0)
        {
            widget->SetWidth(dynamicWidth / dynamicCount);
        }
        else
        {
            widget->SetWidth(widget->GetMaxWidth());
        }

        widget->SetHeight(maxHeight);

        widget->Update();

        dynamicWidth -= widget->GetWidth();
        if (widget->GetMaxWidth() < 0) dynamicCount--;
    }

    Shrink();
}
