// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include <array>
#include <ostream>
#include <vector>

struct RVector2
{
    float x, y;
};

struct RRectangle
{
    float x, y, width, height;

    void SetPosition(RVector2 vec)
    {
        x = vec.x;
        y = vec.y;
    }
    void SetSize(RVector2 vec)
    {
        width = vec.x;
        height = vec.y;
    }

    RVector2 GetPosition() const { return {x, y}; }
    RVector2 GetSize() const { return {width, height}; }

    bool IsInside(RVector2 p)
    {
        return p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height;
    }
};

struct RColor;

RColor HexToRgba(const std::string& hex);

struct RColor
{
    unsigned char r, g, b, a;

    RColor() : r(0), g(0), b(0), a(255) {}
    RColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : r(r), g(g), b(b), a(a)
    {
    }
    RColor(const std::string& hex) { *this = HexToRgba(hex); }
};

struct RTexture
{
    unsigned int id; // OpenGL texture id
    int width;       // Texture base width
    int height;      // Texture base height
    int mipmaps;     // Mipmap levels, 1 by default
    int format;      // Data format (PixelFormat type)
};

struct RFont
{
    typedef struct Rectangle Rectangle;
    typedef struct GlyphInfo GlyphInfo;

    int baseSize;      // Base size (default chars height)
    int glyphCount;    // Number of glyph characters
    int glyphPadding;  // Padding around the glyph characters
    RTexture texture;  // Texture atlas containing the glyphs
    Rectangle* recs;   // Rectangles in texture for the glyphs
    GlyphInfo* glyphs; // Glyphs info data
};

constexpr size_t R_THEME_LIST_SIZE = 5;
enum class RThemeList
{
    Primary,
    Secondary,
    Border,
    Text,
    Background
};

constexpr size_t R_THEME_STATE_SIZE = 5;
enum class RThemeState
{
    Default,
    Hovered,
    Clicked,
    Disabled,
    Highlighted
};

struct RTheme
{
    RColor hoveredTint, clickedTint, disabledTint, highlightedTint;
    std::array<std::array<RColor, R_THEME_STATE_SIZE>, R_THEME_LIST_SIZE> colors;
};

enum class RMouseButton
{
    Left = 0,
    Right = 1,
    Middle = 2,
    Side = 3,
    Extra = 4,
    Forward = 5,
    Back = 6
};

enum class RAlign
{
    Left,
    HCenter,
    Right,
    Top,
    VCenter,
    Bottom
};

float ClampWidth(float val, float min, float max);
float ClampHeight(float val, float min, float max);
RVector2 ClampSize(const RVector2& size, const RVector2& minSize, const RVector2& maxSize);
RRectangle ClampBounds(const RRectangle& bounds, const RVector2& minSize, const RVector2& maxSize);
float MinWidth(float a, float b);
float MinHeight(float a, float b);
RVector2 MinSize(const RVector2& a, const RVector2& b);
float MaxWidth(float a, float b);
float MaxHeight(float a, float b);
RVector2 MaxSize(const RVector2& a, const RVector2& b);
RRectangle AddMargin(const RRectangle& bounds, float margin);
std::wstring StringToWString(const std::string& s);
std::string WStringToString(const std::wstring& s);
std::vector<std::string> Split(const std::string& s, char delimiter = ' ');

std::ostream& operator<<(std::ostream& out, const RVector2& vec);
std::ostream& operator<<(std::ostream& out, const RRectangle& rec);
std::ostream& operator<<(std::ostream& out, const RColor& color);

RVector2 operator+(const RVector2& a, const RVector2& b);
const RVector2& operator+=(RVector2& a, const RVector2& b);
RVector2 operator-(const RVector2& a, const RVector2& b);
const RVector2& operator-=(RVector2& a, const RVector2& b);
RVector2 operator*(const RVector2& a, const float& b);
RVector2 operator*(const RVector2& a, const RVector2& b);
const RVector2& operator*=(RVector2& a, const float& b);
const RVector2& operator*=(RVector2& a, const RVector2& b);
RVector2 operator/(const RVector2& a, const float& b);
RVector2 operator/(const RVector2& a, const RVector2& b);
const RVector2& operator/=(RVector2& a, const float& b);
const RVector2& operator/=(RVector2& a, const RVector2& b);
bool operator==(const RVector2& a, const RVector2& b);
bool operator!=(const RVector2& a, const RVector2& b);

bool operator==(const RRectangle& a, const RRectangle& b);
bool operator!=(const RRectangle& a, const RRectangle& b);

RColor MixColors(const RColor& a, const RColor& b);
bool operator==(const RColor& a, const RColor& b);
bool operator!=(const RColor& a, const RColor& b);
