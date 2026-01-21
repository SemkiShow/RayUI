// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Layouts/RGridLayout.hpp"
#include <algorithm>
#include <cmath>

void RGridLayout::Shrink()
{
    // Calculate total width and height
    float totalWidth = 0, totalHeight = 0;
    {
        int column = 0;
        float currentWidth = 0, currentHeight = 0;
        for (auto& widget: widgets)
        {
            if (!widget->IsVisible()) continue;

            currentWidth += widget->GetWidth() + padding;
            currentHeight = std::max(currentHeight, widget->GetHeight() + padding);

            column++;
            if (column >= columns)
            {
                column = 0;

                totalWidth = std::max(totalWidth, currentWidth);
                totalHeight += currentHeight;
            }
        }
        totalWidth -= padding;
        totalHeight -= padding;
    }

    // Calculate rows count
    int rows = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        rows++;
    }
    rows = std::ceil(rows * 1.0f / columns);

    // Calculate cell widths and heights
    std::vector<float> widths(columns, 0), heights(rows, 0);
    {
        int column = 0, row = 0;
        for (size_t i = 0; i < widgets.size(); i++)
        {
            if (!widgets[i]->IsVisible()) continue;

            widths[column] = std::max(widths[column], widgets[i]->GetWidth());
            heights[row] = std::max(heights[row], widgets[i]->GetHeight());

            column++;
            if (column >= columns)
            {
                column = 0;
                row++;
            }
        }
    }

    // Calculate posX offset
    float posX = GetPositionX() + margin;
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
    float startPosX = posX;

    // Calculate posY offset
    float posY = GetPositionY() + margin;
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

    // Set widget positions
    int column = 0, row = 0;
    float maxPosX = 0, maxPosY = 0;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        RVector2 cellSize = {widths[column], heights[row]};

        {
            float delta = cellSize.x + padding;
            switch (widget->GetAlignH())
            {
            case RAlign::Left:
                break;
            case RAlign::HCenter:
                posX += (cellSize.x - widget->GetWidth()) / 2;
                break;
            case RAlign::Right:
                posX += (cellSize.x - widget->GetWidth()) / 2;
                break;
            default:
                throw std::runtime_error("Invalid alignH set!");
                break;
            }
            widget->SetPositionX(posX);
            posX += delta;
        }

        {
            float widgetPosY = posY;
            switch (widget->GetAlignV())
            {
            case RAlign::Top:
                break;
            case RAlign::VCenter:
                widgetPosY += (cellSize.y - widget->GetHeight()) / 2;
                break;
            case RAlign::Bottom:
                widgetPosY += (cellSize.y - widget->GetHeight());
                break;
            default:
                throw std::runtime_error("Invalid alignV set!");
                break;
            }
            widget->SetPositionY(widgetPosY);
        }

        widget->UpdateBounds();
        widget->Update();

        column++;
        if (column >= columns)
        {
            column = 0;
            maxPosX = std::max(maxPosX, posX);
            posX = startPosX;

            float delta = cellSize.y + padding;
            posY += delta;
            maxPosY = std::max(maxPosY, posY);

            row++;
        }
    }

    // Set shrinked size
    SetWidth(maxPosX - bounds.x - padding + margin);
    SetHeight(maxPosY - bounds.y - padding + margin);
    bounds = ClampBounds(bounds, minSize, maxSize);
}

void RGridLayout::Update()
{
    CleanupWidgets();

    if (!updateBounds)
    {
        RLayout::UpdateWidgets();
        return;
    }

    updateBounds = false;

    // Calculate rows count
    int rows = 0;
    std::vector<std::shared_ptr<RWidget>> visibleWidgets;
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        rows++;
        visibleWidgets.push_back(widget);
    }
    rows = std::ceil(rows * 1.0f / columns);

    // Calculate widths
    int dynamicWidthCount = 0;
    for (int column = 0; column < columns; column++)
    {
        bool foundDynamic = false;
        for (int row = 0; row < rows; row++)
        {
            size_t idx = row * columns + column;
            if (idx >= visibleWidgets.size()) break;

            auto widget = visibleWidgets[idx];

            if (widget->GetMaxWidth() < 0) foundDynamic = true;
        }
        if (foundDynamic) dynamicWidthCount++;
    }
    float dynamicWidth = GetWidth() - 2 * margin - (columns - 1) * padding;

    // Calculate heights
    int dynamicHeightCount = 0;
    for (int row = 0; row < rows; row++)
    {
        bool foundDynamic = false;
        for (int column = 0; column < columns; column++)
        {
            size_t idx = row * columns + column;
            if (idx >= visibleWidgets.size()) break;

            auto widget = visibleWidgets[idx];

            if (widget->GetMaxHeight() < 0) foundDynamic = true;
        }
        if (foundDynamic) dynamicHeightCount++;
    }
    float dynamicHeight = GetHeight() - 2 * margin - (rows - 1) * padding;

    // Update widgets' bounds upfront
    for (auto& widget: widgets)
    {
        widget->UpdateBounds();
    }

    // Set widgets' widths
    for (int column = 0; column < columns; column++)
    {
        float maxWidth = 0;
        bool foundDynamic = false;
        for (int row = 0; row < rows; row++)
        {
            size_t idx = row * columns + column;
            if (idx >= visibleWidgets.size()) break;

            auto widget = visibleWidgets[idx];

            if (widget->GetMaxWidth() < 0)
                widget->SetWidth(dynamicWidth / dynamicWidthCount);
            else
                widget->SetWidth(widget->GetMaxWidth());

            widget->UpdateBounds();
            widget->Update();

            maxWidth = std::max(maxWidth, widget->GetWidth());
            if (widget->GetMaxWidth() < 0) foundDynamic = true;
        }

        dynamicWidth -= maxWidth;
        if (foundDynamic) dynamicWidthCount--;
    }

    // Set widgets' heights
    for (int row = 0; row < rows; row++)
    {
        float maxHeight = 0;
        bool foundDynamic = false;
        for (int column = 0; column < columns; column++)
        {
            size_t idx = row * columns + column;
            if (idx >= visibleWidgets.size()) break;

            auto widget = visibleWidgets[idx];

            if (widget->GetMaxHeight() < 0)
                widget->SetHeight(dynamicHeight / dynamicHeightCount);
            else
                widget->SetHeight(widget->GetMaxHeight());

            widget->UpdateBounds();
            widget->Update();

            maxHeight = std::max(maxHeight, widget->GetHeight());
            if (widget->GetMaxHeight() < 0) foundDynamic = true;
        }

        dynamicHeight -= maxHeight;
        if (foundDynamic) dynamicHeightCount--;
    }

    Shrink();
}
