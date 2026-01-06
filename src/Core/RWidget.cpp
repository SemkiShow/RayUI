// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/RWidget.hpp"
#include "Api.hpp"

void RWidget::ResetEvents()
{
    isMouseHovered = false;
    isMouseLeftDown = false;
    isMouseLeftPressed = false;
    isMouseLeftReleased = false;
    isMouseRightDown = false;
    isMouseRightPressed = false;
    isMouseRightReleased = false;
}

bool RWidget::PollEvents()
{
    bool isInside = bounds.IsInside(rui::GetMousePosition());
    if (!isInside) return false;

    isMouseHovered = isInside;
    isMouseLeftDown = rui::IsMouseButtonDown(RMouseButton::Left);
    isMouseLeftPressed = rui::IsMouseButtonPressed(RMouseButton::Left);
    isMouseLeftReleased = rui::IsMouseButtonReleased(RMouseButton::Left);
    isMouseRightDown = rui::IsMouseButtonDown(RMouseButton::Right);
    isMouseRightPressed = rui::IsMouseButtonPressed(RMouseButton::Right);
    isMouseRightReleased = rui::IsMouseButtonReleased(RMouseButton::Right);
    return true;
}

void RWidget::Update()
{
    UpdateColors();
    if (updateBounds)
    {
        updateBounds = false;
        Shrink();
    }
}

void RWidget::UpdateColors()
{
    if (customColor)
    {
        if (IsMouseHovered())
        {
            color = MixColors(tint, GetTheme()->hoveredTint);
            if (IsMouseLeftDown())
            {
                color = MixColors(tint, GetTheme()->clickedTint);
            }
        }
        else if (disabled)
        {
            color = MixColors(tint, GetTheme()->disabledTint);
        }
        else if (highlighted)
        {
            color = MixColors(tint, GetTheme()->highlightedTint);
        }
        else
        {
            color = tint;
        }
    }
    else
    {
        if (IsMouseHovered())
        {
            color = GetThemeColor(RThemeState::Hovered);
            if (IsMouseLeftDown())
            {
                color = GetThemeColor(RThemeState::Clicked);
            }
        }
        else if (disabled)
        {
            color = GetThemeColor(RThemeState::Disabled);
        }
        else if (highlighted)
        {
            color = GetThemeColor(RThemeState::Highlighted);
        }
        else
        {
            color = GetThemeColor(RThemeState::Default);
        }
    }
}
