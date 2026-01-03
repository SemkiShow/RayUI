// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Utils.hpp"

namespace rui
{
float GetWindowWidth();
float GetWindowHeight();
RVector2 GetWindowSize();

void DrawRectangle(RRectangle rec, RColor color);
void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color);
} // namespace rui
