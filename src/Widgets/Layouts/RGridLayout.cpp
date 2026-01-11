// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RGridLayout.hpp"
#include <algorithm>
#include <cmath>

void RGridLayout::Shrink()
{
    // Calculate shrinked size
    RVector2 newSize = {2 * margin, 2 * margin};
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;
        newSize += widget->GetSize();
        newSize.x += padding;
        newSize.y += padding;
    }
    newSize.x -= padding;
    newSize.y -= padding;

    // Calculate rows count
    int rowsCount = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        rowsCount++;
    }
    rowsCount = std::ceil(rowsCount * 1.0f / columns);

    // Calculate cell widths and heights
    std::vector<float> widths(columns, 0), heights(rowsCount, 0);
    for (size_t i = 0; i < widgets.size(); i++)
    {
        widths[i % columns] = std::max(widths[i % columns], widgets[i]->GetWidth());
        heights[i / columns] = std::max(heights[i / columns], widgets[i]->GetHeight());
    }

    // Calculate additional width to spread the widgets
    std::vector<float> reservedWidths(columns, 0);
    {
        int idx = 0;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            reservedWidths[idx] += widget->GetWidth();

            idx++;
            idx %= columns;
        }
    }
    float reservedWidth = *std::max_element(reservedWidths.begin(), reservedWidths.end());
    float additionalWidth = (GetWidth() - reservedWidth);
    additionalWidth = fmax(0, additionalWidth);
    if (columns > 0) additionalWidth /= columns;

    int row = 0, column = 0;
    RVector2 pos = bounds.GetPosition();
    pos.x += margin;
    pos.y += margin;
    for (auto& widget: widgets)
    {
        auto widgetPos = pos;
        RVector2 cellSize = {widths[column], heights[row]};

        switch (widget->GetAlignH())
        {
        case RAlign::Left:
            break;
        case RAlign::HCenter:
            widgetPos.x += (cellSize.x - widget->GetWidth()) / 2;
            break;
        case RAlign::Right:
            widgetPos.x += (cellSize.x - widget->GetWidth());
            break;
        default:
            throw std::runtime_error("Invalid alignH set!");
            break;
        }

        switch (widget->GetAlignV())
        {
        case RAlign::Top:
            break;
        case RAlign::VCenter:
            widgetPos.y += (cellSize.y - widget->GetHeight()) / 2;
            break;
        case RAlign::Bottom:
            widgetPos.y += (cellSize.y - widget->GetHeight());
            break;
        default:
            throw std::runtime_error("Invalid alignV set!");
            break;
        }

        widget->SetPosition(widgetPos);

        column++;
        pos.x += cellSize.x + padding + additionalWidth;
        if (column >= columns)
        {
            column = 0;
            row++;
            pos.x = GetPositionX() + margin;
            pos.y += cellSize.y + padding;
        }
    }

    // Set shrinked size
    SetWidth(std::max(bounds.width, newSize.x));
    SetHeight(std::max(bounds.height, newSize.y));
    bounds = ClampBounds(bounds, minSize, maxSize);
}

void RGridLayout::Update()
{
    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

    updateBounds = false;

    // Calculate rows count
    int rowsCount = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        rowsCount++;
    }
    rowsCount = std::ceil(rowsCount * 1.0f / columns);

    // Calculate heights
    std::vector<float> fixedHeights(columns, 0);
    std::vector<int> dynamicHeightCounts(columns, 0);
    {
        int idx = 0;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            if (widget->GetMaxHeight() < 0)
                dynamicHeightCounts[idx]++;
            else
                fixedHeights[idx] += widget->GetMaxHeight();

            idx++;
            idx %= columns;
        }
    }
    float fixedHeight = *std::max_element(fixedHeights.begin(), fixedHeights.end());
    int dynamicHeightCount =
        *std::max_element(dynamicHeightCounts.begin(), dynamicHeightCounts.end());
    float dynamicHeight = GetHeight() - 2 * margin - (rowsCount - 1) * padding - fixedHeight;
    dynamicHeight = fmax(0, dynamicHeight);
    if (dynamicHeightCount > 0) dynamicHeight /= dynamicHeightCount;

    // Calculate widths
    std::vector<float> fixedWidths(columns, 0);
    std::vector<int> dynamicWidthCounts(columns, 0);
    {
        int idx = 0;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            if (widget->GetMaxWidth() < 0)
                dynamicWidthCounts[idx]++;
            else
                fixedWidths[idx] += widget->GetMaxWidth();

            idx++;
            idx %= columns;
        }
    }
    float fixedWidth = *std::max_element(fixedWidths.begin(), fixedWidths.end());
    int dynamicWidthCount = *std::max_element(dynamicWidthCounts.begin(), dynamicWidthCounts.end());
    float dynamicWidth = GetWidth() - 2 * margin - (columns - 1) * padding - fixedWidth;
    dynamicWidth = fmax(0, dynamicWidth);
    if (dynamicWidthCount > 0) dynamicWidth /= dynamicWidthCount;

    for (auto& widget: widgets)
    {
        if (widget->GetMaxHeight() < 0)
            widget->SetHeight(dynamicHeight);
        else
            widget->SetHeight(widget->GetMaxHeight());

        if (widget->GetMaxWidth() < 0)
            widget->SetWidth(dynamicWidth);
        else
            widget->SetWidth(widget->GetMaxWidth());
    }

    // Update widgets
    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->UpdateBounds();
    }
    RLayout::UpdateWidgets();

    Shrink();
}
