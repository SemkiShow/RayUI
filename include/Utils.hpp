// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

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
};

struct RColor
{
    unsigned char r, g, b, a;

    RColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : r(r), g(g), b(b), a(a)
    {
    }
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

bool operator==(const RColor& a, const RColor& b);
bool operator!=(const RColor& a, const RColor& b);
