// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RVBoxLayout.hpp"
#include <cmath>

void RVBoxLayout::ShrinkToContent()
{
    int visibleCount = 0;
    float maxWidth = 0, totalHeight = 0;
    for (auto& widget: widgets)
    {
        if (widget->IsVisible())
        {
            widget->ShrinkToContent();
            visibleCount++;
            maxWidth = std::max(maxWidth, widget->GetWidth());
            totalHeight += widget->GetHeight() + padding;
        }
    }
    totalHeight -= padding;

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

    float posY = GetPositionY() + margin, heightLeft = totalHeight;
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

    RVector2 newSize{maxWidth, 2 * margin};
    if (visibleCount > 0) newSize.y += posY - margin - padding - GetPositionY();
    SetSize(newSize);
}

void RVBoxLayout::Update()
{
    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

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

    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->UpdateBounds();
    }

    RLayout::UpdateWidgets();

    ShrinkToContent();
}
