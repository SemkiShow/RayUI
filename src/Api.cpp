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

void DrawRectangle(RRectangle rec, RColor color)
{
    ::DrawRectangleRec(ToRaylib(rec), ToRaylib(color));
}

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color)
{
    ::DrawRectangleRounded(ToRaylib(rec), roundness, segments, ToRaylib(color));
}

} // namespace rui
