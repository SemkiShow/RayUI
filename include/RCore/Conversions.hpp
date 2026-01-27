// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief Functions for converting from/to raylib types to/from RayUI types
 */

#pragma once

#include "RCore/Utils.hpp"

typedef struct Vector2 Vector2;
typedef struct Rectangle Rectangle;
typedef struct Color Color;
typedef struct Texture Texture;
typedef struct Font Font;

namespace rui
{

/**
 * @defgroup Conversions
 * @brief Functions for converting from/to raylib types to/from RayUI types
 * @{
 */

::Vector2 ToRaylib(RVector2 vec);
::Rectangle ToRaylib(RRectangle rec);
::Color ToRaylib(RColor color);
::Texture ToRaylib(RTexture texture);
::Font ToRaylib(RFont font);

RVector2 FromRaylib(::Vector2 vec);
RRectangle FromRaylib(::Rectangle rec);
RColor FromRaylib(::Color color);
RTexture FromRaylib(::Texture texture);
RFont FromRaylib(::Font font);

/** @} */

} // namespace rui
