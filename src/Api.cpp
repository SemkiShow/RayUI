// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include <raylib.h>
#include <raymath.h>

namespace rui
{

inline ::Vector2 ToRaylib(RVector2 vec) { return {vec.x, vec.y}; }
inline ::Rectangle ToRaylib(RRectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
inline ::Color ToRaylib(RColor color) { return {color.r, color.g, color.b, color.a}; }

inline RVector2 FromRaylib(::Vector2 vec) { return {vec.x, vec.y}; }
inline RRectangle FromRaylib(::Rectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
inline RColor FromRaylib(::Color color) { return {color.r, color.g, color.b, color.a}; }

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
