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
    if (updateBounds)
    {
        updateBounds = false;
        Shrink();
    }
}
