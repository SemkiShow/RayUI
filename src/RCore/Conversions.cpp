// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/Conversions.hpp"
#include <raylib.h>

namespace rui
{

::Vector2 ToRaylib(RVector2 vec) { return {vec.x, vec.y}; }
::Rectangle ToRaylib(RRectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
::Color ToRaylib(RColor color) { return {color.r, color.g, color.b, color.a}; }
::Texture ToRaylib(RTexture texture)
{
    return {texture.id, texture.width, texture.height, texture.mipmaps, texture.format};
}
::Font ToRaylib(RFont font)
{
    return {font.baseSize,          font.glyphCount, font.glyphPadding,
            ToRaylib(font.texture), font.recs,       font.glyphs};
}

RVector2 FromRaylib(::Vector2 vec) { return {vec.x, vec.y}; }
RRectangle FromRaylib(::Rectangle rec) { return {rec.x, rec.y, rec.width, rec.height}; }
RColor FromRaylib(::Color color) { return {color.r, color.g, color.b, color.a}; }
RTexture FromRaylib(::Texture texture)
{
    return {texture.id, texture.width, texture.height, texture.mipmaps, texture.format};
}
RFont FromRaylib(::Font font)
{
    return {font.baseSize, font.glyphCount, font.glyphPadding, FromRaylib(font.texture),
            font.recs,     font.glyphs};
}

} // namespace rui
