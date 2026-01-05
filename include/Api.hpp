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

RVector2 GetMousePosition();
bool IsMouseButtonPressed(RMouseButton button);
bool IsMouseButtonReleased(RMouseButton button);
bool IsMouseButtonDown(RMouseButton button);
bool IsMouseButtonUp(RMouseButton button);

void DrawRectangle(RRectangle rec, RColor color);
void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color);
void DrawText(const std::string& text, RVector2 pos, float fontSize, RColor color);
void DrawTextFont(RFont font, const std::string& text, RVector2 pos, float fontSize, float spacing, RColor color);
RVector2 MeasureText(const std::string& text, float fontSize);
RVector2 MeasureTextFont(RFont font, const std::string& text, float fontSize, float spacing);

} // namespace rui
