// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Utils.hpp"

namespace rui
{

enum class MouseButton
{
    Left = 0,
    Right = 1,
    Middle = 2,
    Side = 3,
    Extra = 4,
    Forward = 5,
    Back = 6
};

float GetWindowWidth();
float GetWindowHeight();
RVector2 GetWindowSize();

RVector2 GetMousePosition();
bool IsMouseButtonPressed(MouseButton button);
bool IsMouseButtonReleased(MouseButton button);
bool IsMouseButtonDown(MouseButton button);
bool IsMouseButtonUp(MouseButton button);

void DrawRectangle(RRectangle rec, RColor color);
void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color);

} // namespace rui
