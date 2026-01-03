// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Conversions.hpp"
#include <raylib.h>

namespace rui
{

float GetWindowWidth() { return static_cast<float>(GetRenderWidth()) / GetWindowScaleDPI().x; }

float GetWindowHeight() { return static_cast<float>(GetRenderHeight()) / GetWindowScaleDPI().y; }

RVector2 GetWindowSize() { return {GetWindowWidth(), GetWindowHeight()}; }

RVector2 GetMousePosition() { return FromRaylib(::GetMousePosition()); }

bool IsMouseButtonPressed(MouseButton button)
{
    return ::IsMouseButtonPressed(static_cast<int>(button));
}

bool IsMouseButtonReleased(MouseButton button)
{
    return ::IsMouseButtonReleased(static_cast<int>(button));
}

bool IsMouseButtonDown(MouseButton button) { return ::IsMouseButtonDown(static_cast<int>(button)); }

bool IsMouseButtonUp(MouseButton button) { return ::IsMouseButtonUp(static_cast<int>(button)); }

void DrawRectangle(RRectangle rec, RColor color)
{
    ::DrawRectangleRec(ToRaylib(rec), ToRaylib(color));
}

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color)
{
    ::DrawRectangleRounded(ToRaylib(rec), roundness, segments, ToRaylib(color));
}

} // namespace rui
