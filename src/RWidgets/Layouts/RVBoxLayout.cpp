// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Layouts/RVBoxLayout.hpp"

void RVBoxLayout::Shrink()
{
    // Calculate shrinked size
    float newWidth = 0, totalHeight = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        newWidth = std::max(newWidth, widget->GetWidth() + 2 * margin);
        totalHeight += widget->GetHeight() + padding;
    }
    totalHeight -= padding;

    // Calculate center widgets' height
    bool foundFirstCenter = false;
    float centerHeight = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetAlignV() == RAlign::VCenter) foundFirstCenter = true;
        if (widget->GetAlignV() == RAlign::Bottom) break;
        if (!foundFirstCenter) continue;

        centerHeight += widget->GetHeight() + padding;
    }
    centerHeight -= padding;

    // Calculate posY offset
    float posY = GetPositionY() + margin, heightLeft = totalHeight;
    switch (GetAlignV())
    {
    case RAlign::Top:
        break;
    case RAlign::VCenter:
        posY += (GetHeight() - 2 * margin - totalHeight) / 2;
        break;
    case RAlign::Bottom:
        posY += (GetHeight() - 2 * margin - totalHeight);
        break;
    default:
        throw std::runtime_error("Invalid alignV set!");
        break;
    }

    // Set widgets' positions
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        switch (widget->GetAlignH())
        {
        case RAlign::Left:
            widget->SetPositionX(GetPositionX() + margin);
            break;
        case RAlign::HCenter:
            widget->SetPositionX(GetPositionX() + margin +
                                 (GetWidth() - 2 * margin - widget->GetWidth()) / 2);
            break;
        case RAlign::Right:
            widget->SetPositionX(GetPositionX() + margin +
                                 (GetWidth() - 2 * margin - widget->GetWidth()));
            break;
        default:
            throw std::runtime_error("Invalid alignH set!");
            break;
        }

        float delta = widget->GetHeight() + padding;
        switch (widget->GetAlignV())
        {
        case RAlign::Top:
            break;
        case RAlign::VCenter:
            posY = std::max(posY, GetPositionY() + margin +
                                      (GetHeight() - 2 * margin - centerHeight) / 2);
            break;
        case RAlign::Bottom:
            posY =
                std::max(posY, GetPositionY() + margin + (GetHeight() - 2 * margin - heightLeft));
            break;
        default:
            throw std::runtime_error("Invalid alignV set!");
            break;
        }
        widget->SetPositionY(posY);
        posY += delta;
        heightLeft -= delta;

        widget->UpdateBounds();
        widget->Update();
    }

    // Set shrinked size
    bool allLeft = true;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        if (widget->GetAlignH() != RAlign::Left)
        {
            allLeft = false;
            break;
        }
    }
    if (allLeft)
        SetWidth(newWidth + 2 * margin);
    else
        SetWidth(std::max(bounds.width, newWidth + 2 * margin));
    SetHeight(posY - bounds.y - padding + margin);
    bounds = ClampBounds(bounds, minSize, maxSize);
}

void RVBoxLayout::Update()
{
    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

    updateBounds = false;

    // Calculate heights
    int visibleCount = 0, dynamicCount = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            if (widget->GetMaxHeight() < 0) dynamicCount++;
            visibleCount++;
        }
    }
    float dynamicHeight = GetHeight() - 2 * margin - (visibleCount - 1) * padding;

    if (visibleCount == 0) return;

    // Update widgets' bounds upfront
    for (auto& widget: widgets)
    {
        widget->UpdateBounds();
    }

    // Set widgets' sizes
    float maxWidth = GetWidth() - 2 * margin;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        widget->SetWidth(maxWidth);

        if (widget->GetMaxHeight() < 0)
        {
            widget->SetHeight(dynamicHeight / dynamicCount);
        }
        else
        {
            widget->SetHeight(widget->GetMaxHeight());
        }

        widget->Update();

        dynamicHeight -= widget->GetHeight();
        if (widget->GetMaxHeight() < 0) dynamicCount--;
    }

    Shrink();
}
