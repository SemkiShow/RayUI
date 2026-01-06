// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RVBoxLayout.hpp"
#include <cmath>

void RVBoxLayout::Shrink()
{
    // Calculate shrinked size
    float newWidth = 0, totalHeight = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            newWidth = std::max(newWidth, widget->GetWidth() + 2 * margin);
            totalHeight += widget->GetHeight() + padding;
        }
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
    SetWidth(newWidth + 2 * margin);
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

    // Set widgets' sizes
    float maxWidth = GetWidth() - 2 * margin;
    float dynamicHeight = GetHeight() - 2 * margin - (visibleCount - 1) * padding - fixedHeight;
    dynamicHeight = fmax(0, dynamicHeight);
    if (dynamicCount > 0) dynamicHeight /= dynamicCount;
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
    }

    // Update widgets
    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->UpdateBounds();
    }
    RLayout::UpdateWidgets();

    Shrink();
}
