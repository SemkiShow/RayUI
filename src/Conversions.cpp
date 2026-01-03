// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Conversions.hpp"
#include <raylib.h>

namespace rui
{

::Vector2 ToRaylib(RVector2 vec) { return {vec.x, vec.y}; }
::Rectangle ToRaylib(RRectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
::Color ToRaylib(RColor color) { return {color.r, color.g, color.b, color.a}; }

RVector2 FromRaylib(::Vector2 vec) { return {vec.x, vec.y}; }
RRectangle FromRaylib(::Rectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
RColor FromRaylib(::Color color) { return {color.r, color.g, color.b, color.a}; }

} // namespace rui
