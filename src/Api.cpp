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

bool IsMouseButtonPressed(RMouseButton button)
{
    return ::IsMouseButtonPressed(static_cast<int>(button));
}

bool IsMouseButtonReleased(RMouseButton button)
{
    return ::IsMouseButtonReleased(static_cast<int>(button));
}

bool IsMouseButtonDown(RMouseButton button)
{
    return ::IsMouseButtonDown(static_cast<int>(button));
}

bool IsMouseButtonUp(RMouseButton button) { return ::IsMouseButtonUp(static_cast<int>(button)); }

void DrawRectangle(RRectangle rec, RColor color)
{
    ::DrawRectangleRec(ToRaylib(rec), ToRaylib(color));
}

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color)
{
    ::DrawRectangleRounded(ToRaylib(rec), roundness, segments, ToRaylib(color));
}

void DrawText(const std::string& text, RVector2 pos, float fontSize, RColor color)
{
    ::DrawText(text.c_str(), pos.x, pos.y, fontSize, ToRaylib(color));
}

void DrawTextFont(RFont font, const std::string& text, RVector2 pos, float fontSize, float spacing,
                  RColor color)
{
    ::DrawTextEx(ToRaylib(font), text.c_str(), ToRaylib(pos), fontSize, spacing, ToRaylib(color));
}

RVector2 MeasureText(const std::string& text, float fontSize)
{
    auto res = ::MeasureText(text.c_str(), fontSize);
    return {static_cast<float>(res), fontSize};
}

RVector2 MeasureTextFont(RFont font, const std::string& text, float fontSize, float spacing)
{
    auto res = ::MeasureTextEx(ToRaylib(font), text.c_str(), fontSize, spacing);
    return FromRaylib(res);
}

} // namespace rui
