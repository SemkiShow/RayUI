// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Utils.hpp"
#include <algorithm>
#include <codecvt>
#include <locale>

float ClampWidth(float val, float min, float max)
{
    if (min < 0) return -1;
    if (max < 0) return std::max(min, val);
    return std::max(min, std::min(max, val));
}

float ClampHeight(float val, float min, float max) { return ClampWidth(val, min, max); }

RVector2 ClampSize(const RVector2& size, const RVector2& minSize, const RVector2& maxSize)
{
    RVector2 vec;
    vec.x = ClampWidth(size.x, minSize.x, maxSize.x);
    vec.y = ClampHeight(size.y, minSize.y, maxSize.y);
    return vec;
}

RRectangle ClampBounds(const RRectangle& bounds, const RVector2& minSize, const RVector2& maxSize)
{
    auto rec = bounds;
    rec.SetSize(ClampSize(rec.GetSize(), minSize, maxSize));
    return rec;
}

float MinWidth(float a, float b)
{
    if (a < 0 && b < 0) return -1;
    if (a < 0 || b < 0) return std::max(a, b);
    return std::min(a, b);
}

float MinHeight(float a, float b) { return MinWidth(a, b); }

RVector2 MinSize(const RVector2& a, const RVector2& b)
{
    return {MinWidth(a.x, b.x), MinHeight(a.y, b.y)};
}

float MaxWidth(float a, float b)
{
    if (a < 0 || b < 0) return -1;
    return std::max(a, b);
}

float MaxHeight(float a, float b) { return MaxWidth(a, b); }

RVector2 MaxSize(const RVector2& a, const RVector2& b)
{
    return {MaxWidth(a.x, b.x), MaxHeight(a.y, b.y)};
}

RRectangle AddMargin(const RRectangle& bounds, float margin)
{
    auto rec = bounds;
    rec.x += margin;
    rec.y += margin;
    rec.width -= 2 * margin;
    rec.height -= 2 * margin;
    return rec;
}

std::wstring StringToWString(const std::string& s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}

std::string WStringToString(const std::wstring& s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(s);
}

std::vector<std::string> Split(const std::string& s, char delimiter)
{
    std::vector<std::string> out(1, "");
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == delimiter)
        {
            out.push_back("");
            continue;
        }
        out.back() += s[i];
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const RVector2& vec)
{
    out << std::to_string(vec.x) << ' ' << std::to_string(vec.y);
    return out;
}

std::ostream& operator<<(std::ostream& out, const RRectangle& rec)
{
    out << std::to_string(rec.x) << ' ' << std::to_string(rec.y) << ' ' << std::to_string(rec.width)
        << ' ' << std::to_string(rec.height);
    return out;
}

std::ostream& operator<<(std::ostream& out, const RColor& color)
{
    out << std::to_string(color.r) << ' ' << std::to_string(color.g) << ' '
        << std::to_string(color.b) << ' ' << std::to_string(color.a);
    return out;
}

RVector2 operator+(const RVector2& a, const RVector2& b) { return {a.x + b.x, a.y + b.y}; }

const RVector2& operator+=(RVector2& a, const RVector2& b) { return a = a + b; }

RVector2 operator-(const RVector2& a, const RVector2& b) { return {a.x - b.x, a.y - b.y}; }

const RVector2& operator-=(RVector2& a, const RVector2& b) { return a = a - b; }

RVector2 operator*(const RVector2& a, const float& b) { return {a.x * b, a.y * b}; }

RVector2 operator*(const RVector2& a, const RVector2& b) { return {a.x * b.x, a.y * b.y}; }

const RVector2& operator*=(RVector2& a, const float& b) { return a = a * b; }

const RVector2& operator*=(RVector2& a, const RVector2& b) { return a = a * b; }

RVector2 operator/(const RVector2& a, const float& b) { return {a.x / b, a.y / b}; }

RVector2 operator/(const RVector2& a, const RVector2& b) { return {a.x / b.x, a.y / b.y}; }

const RVector2& operator/=(RVector2& a, const float& b) { return a = a / b; }

const RVector2& operator/=(RVector2& a, const RVector2& b) { return a = a / b; }

bool operator==(const RVector2& a, const RVector2& b) { return a.x == b.x && a.y == b.x; }

bool operator!=(const RVector2& a, const RVector2& b) { return a.x != b.x || a.y != b.y; }

bool operator==(const RRectangle& a, const RRectangle& b)
{
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

bool operator!=(const RRectangle& a, const RRectangle& b) { return !(a == b); }

bool operator==(const RColor& a, const RColor& b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool operator!=(const RColor& a, const RColor& b) { return !(a == b); }
