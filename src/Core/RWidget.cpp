// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Core/RWidget.hpp"

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
    isMouseLeftDown = rui::IsMouseButtonDown(rui::MouseButton::Left);
    isMouseLeftPressed = rui::IsMouseButtonPressed(rui::MouseButton::Left);
    isMouseLeftReleased = rui::IsMouseButtonReleased(rui::MouseButton::Left);
    isMouseRightDown = rui::IsMouseButtonDown(rui::MouseButton::Right);
    isMouseRightPressed = rui::IsMouseButtonPressed(rui::MouseButton::Right);
    isMouseRightReleased = rui::IsMouseButtonReleased(rui::MouseButton::Right);
    return true;
}

void RWidget::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
    }
}
