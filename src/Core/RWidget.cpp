// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/RWidget.hpp"
#include "Core/Api.hpp"

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
        bounds = ClampBounds(bounds, minSize, maxSize);
        Shrink();
    }
}

void RWidget::UpdateColors()
{
    if (customColor)
    {
        if (IsMouseLeftDown() && isAnimated && isClickable)
        {
            color = MixColors(tint, GetTheme()->clickedTint);
        }
        else if (IsMouseHovered() && isAnimated && isHoverable)
        {
            color = MixColors(tint, GetTheme()->hoveredTint);
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
        if (IsMouseLeftDown() && isAnimated && isClickable)
        {
            themeState = RThemeState::Clicked;
        }
        else if (IsMouseHovered() && isAnimated && isHoverable)
        {
            themeState = RThemeState::Hovered;
        }
        else if (disabled)
        {
            themeState = RThemeState::Disabled;
        }
        else if (highlighted)
        {
            themeState = RThemeState::Highlighted;
        }
        else
        {
            themeState = RThemeState::Default;
        }
        color = GetThemeColor();
    }
}
