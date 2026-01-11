// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include <memory>
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

enum class RKey
{
    Null = 0, // Key: NULL, used for no key pressed
    // Alphanumeric keys
    Apostrophe = 39,   // Key: '
    Comma = 44,        // Key: ,
    Minus = 45,        // Key: -
    Period = 46,       // Key: .
    Slash = 47,        // Key: /
    Zero = 48,         // Key: 0
    One = 49,          // Key: 1
    Two = 50,          // Key: 2
    Three = 51,        // Key: 3
    Four = 52,         // Key: 4
    Five = 53,         // Key: 5
    Six = 54,          // Key: 6
    Seven = 55,        // Key: 7
    Eight = 56,        // Key: 8
    Nine = 57,         // Key: 9
    Semicolon = 59,    // Key: ;
    Equal = 61,        // Key: =
    A = 65,            // Key: A | a
    B = 66,            // Key: B | b
    C = 67,            // Key: C | c
    D = 68,            // Key: D | d
    E = 69,            // Key: E | e
    F = 70,            // Key: F | f
    G = 71,            // Key: G | g
    H = 72,            // Key: H | h
    I = 73,            // Key: I | i
    J = 74,            // Key: J | j
    K = 75,            // Key: K | k
    L = 76,            // Key: L | l
    M = 77,            // Key: M | m
    N = 78,            // Key: N | n
    O = 79,            // Key: O | o
    P = 80,            // Key: P | p
    Q = 81,            // Key: Q | q
    R = 82,            // Key: R | r
    S = 83,            // Key: S | s
    T = 84,            // Key: T | t
    U = 85,            // Key: U | u
    V = 86,            // Key: V | v
    W = 87,            // Key: W | w
    X = 88,            // Key: X | x
    Y = 89,            // Key: Y | y
    Z = 90,            // Key: Z | z
    LeftBracket = 91,  // Key: [
    Backslash = 92,    // Key: '\'
    RightBracket = 93, // Key: ]
    Grave = 96,        // Key: `
    // Function keys
    Space = 32,         // Key: Space
    Escape = 256,       // Key: Esc
    Enter = 257,        // Key: Enter
    Tab = 258,          // Key: Tab
    Backspace = 259,    // Key: Backspace
    Insert = 260,       // Key: Ins
    Delete = 261,       // Key: Del
    Right = 262,        // Key: Cursor right
    Left = 263,         // Key: Cursor left
    Down = 264,         // Key: Cursor down
    Up = 265,           // Key: Cursor up
    PageUp = 266,       // Key: Page up
    PageDown = 267,     // Key: Page down
    Home = 268,         // Key: Home
    End = 269,          // Key: End
    CapsLock = 280,     // Key: Caps lock
    ScrollLock = 281,   // Key: Scroll down
    NumLock = 282,      // Key: Num lock
    PrintScreen = 283,  // Key: Print screen
    Pause = 284,        // Key: Pause
    F1 = 290,           // Key: F1
    F2 = 291,           // Key: F2
    F3 = 292,           // Key: F3
    F4 = 293,           // Key: F4
    F5 = 294,           // Key: F5
    F6 = 295,           // Key: F6
    F7 = 296,           // Key: F7
    F8 = 297,           // Key: F8
    F9 = 298,           // Key: F9
    F10 = 299,          // Key: F10
    F11 = 300,          // Key: F11
    F12 = 301,          // Key: F12
    LeftShift = 340,    // Key: Shift left
    LeftControl = 341,  // Key: Control left
    LeftAlt = 342,      // Key: Alt left
    LeftSuper = 343,    // Key: Super left
    RightShift = 344,   // Key: Shift right
    RightControl = 345, // Key: Control right
    RightAlt = 346,     // Key: Alt right
    RightSuper = 347,   // Key: Super right
    KbMenu = 348,       // Key: KB menu
    // Keypad keys
    KP0 = 320,        // Key: Keypad 0
    KP1 = 321,        // Key: Keypad 1
    KP2 = 322,        // Key: Keypad 2
    KP3 = 323,        // Key: Keypad 3
    KP4 = 324,        // Key: Keypad 4
    KP5 = 325,        // Key: Keypad 5
    KP6 = 326,        // Key: Keypad 6
    KP7 = 327,        // Key: Keypad 7
    KP8 = 328,        // Key: Keypad 8
    KP9 = 329,        // Key: Keypad 9
    KPDecimal = 330,  // Key: Keypad .
    KPDivide = 331,   // Key: Keypad /
    KPMultiply = 332, // Key: Keypad *
    KPSubtract = 333, // Key: Keypad -
    KPAdd = 334,      // Key: Keypad +
    KPEnter = 335,    // Key: Keypad Enter
    KPEqual = 336,    // Key: Keypad =
    // Android key buttons
    Back = 4,       // Key: Android back button
    Menu = 5,       // Key: Android menu button
    VolumeUp = 24,  // Key: Android volume up button
    VolumeDown = 25 // Key: Android volume down button
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

std::string GetCharsPressed();
void Utf8PopBack(std::string& s);

float Map(float val, float oldMin, float oldMax, float newMin, float newMax);

enum class RThemeState;
struct RTheme;

namespace rui
{

void DrawRectangleBorder(RRectangle rec, float borderThickness, RColor color, RTheme theme,
                         RThemeState themeState);

void DrawRectangleRoundedBorder(RRectangle rec, float roundness, int segments,
                                float borderThickness, RColor color, RTheme theme,
                                RThemeState themeState);

void DrawCircleBorder(RVector2 pos, float radius, float borderThickness, int segments, RColor color,
                      RTheme theme, RThemeState themeState);

void DrawText(std::shared_ptr<RFont> font, const std::string& text, RVector2 pos, float fontSize,
              float spacing, RColor color);

RVector2 MeasureText(std::shared_ptr<RFont> font, const std::string& text, float fontSize,
                     float spacing);

} // namespace rui

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
