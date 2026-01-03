// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Utils.hpp"

typedef struct Vector2 Vector2;
typedef struct Rectangle Rectangle;
typedef struct Color Color;

namespace rui
{

::Vector2 ToRaylib(RVector2 vec);
::Rectangle ToRaylib(RRectangle rec);
::Color ToRaylib(RColor color);

RVector2 FromRaylib(::Vector2 vec);
RRectangle FromRaylib(::Rectangle rec);
RColor FromRaylib(::Color color);

} // namespace rui
