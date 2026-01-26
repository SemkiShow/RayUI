// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/Api.hpp"
#include "RCore/Conversions.hpp"
#include <algorithm>
#include <raylib.h>
#include <stack>

namespace rui
{

float GetWindowWidth() { return static_cast<float>(GetRenderWidth()) / GetWindowScaleDPI().x; }

float GetWindowHeight() { return static_cast<float>(GetRenderHeight()) / GetWindowScaleDPI().y; }

RVector2 GetWindowSize() { return {GetWindowWidth(), GetWindowHeight()}; }

RVector2 GetMousePosition() { return FromRaylib(::GetMousePosition()); }

RVector2 GetMouseWheelMove() { return FromRaylib(::GetMouseWheelMoveV()); }

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

bool IsKeyPressed(RKey key) { return ::IsKeyPressed(static_cast<int>(key)); }

bool IsKeyReleased(RKey key) { return ::IsKeyReleased(static_cast<int>(key)); }

bool IsKeyDown(RKey key) { return ::IsKeyDown(static_cast<int>(key)); }

bool IsKeyUp(RKey key) { return ::IsKeyUp(static_cast<int>(key)); }

const char* CodepointToUtf8(int codepoint, int* utf8Size)
{
    return ::CodepointToUTF8(codepoint, utf8Size);
}

int GetCharPressed() { return ::GetCharPressed(); }

void GetCodepointNext(const char* text, int* codepointSize)
{
    ::GetCodepointNext(text, codepointSize);
}

void DrawRectangle(RRectangle rec, RColor color)
{
    ::DrawRectangleRec(ToRaylib(rec), ToRaylib(color));
}

void DrawRectangleLines(RRectangle rec, float lineThickness, RColor color)
{
    ::DrawRectangleLinesEx(ToRaylib(rec), lineThickness, ToRaylib(color));
}

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color)
{
    ::DrawRectangleRounded(ToRaylib(rec), roundness, segments, ToRaylib(color));
}

void DrawRectangleRoundedLines(RRectangle rec, float roundness, int segments, float lineThickness,
                               RColor color)
{
    ::DrawRectangleRoundedLinesEx(ToRaylib(rec), roundness, segments, lineThickness,
                                  ToRaylib(color));
}

void DrawCircle(RVector2 pos, float radius, RColor color)
{
    ::DrawCircle(pos.x, pos.y, radius, ToRaylib(color));
}

void DrawCircleLines(RVector2 pos, float radius, float lineThickness, int segments, RColor color)
{
    ::DrawRing(ToRaylib(pos), radius - lineThickness / 2, radius + lineThickness / 2, 0, 360,
               segments, ToRaylib(color));
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
    return {static_cast<float>(res), fontSize * (std::count(text.begin(), text.end(), '\n') + 1)};
}

RVector2 MeasureTextFont(RFont font, const std::string& text, float fontSize, float spacing)
{
    auto res = ::MeasureTextEx(ToRaylib(font), text.c_str(), fontSize, spacing);
    return FromRaylib(res);
}

std::stack<RRectangle> scissorRecs;

void BeginScissorMode(RRectangle rec)
{
    if (!scissorRecs.empty())
    {
        auto recEndPos = rec.GetPosition() + rec.GetSize();
        auto scissorEndPos = scissorRecs.top().GetPosition() + scissorRecs.top().GetSize();
        RVector2 endPos;
        endPos.x = std::min(recEndPos.x, scissorEndPos.x);
        endPos.y = std::min(recEndPos.y, scissorEndPos.y);
        rec.x = std::max(rec.x, scissorRecs.top().x);
        rec.y = std::max(rec.y, scissorRecs.top().y);
        rec.width = endPos.x - rec.x;
        rec.height = endPos.y - rec.y;
    }
    ::BeginScissorMode(rec.x, rec.y, rec.width, rec.height);
    scissorRecs.push(rec);
}

void EndScissorMode()
{
    scissorRecs.pop();
    ::EndScissorMode();
    if (!scissorRecs.empty())
    {
        ::BeginScissorMode(scissorRecs.top().x, scissorRecs.top().y, scissorRecs.top().width,
                           scissorRecs.top().height);
    }
}

void DrawTexture(RTexture texture, RRectangle rec, RColor tint)
{
    ::DrawTexturePro(ToRaylib(texture),
                     {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                     ToRaylib(rec), {0, 0}, 0, ToRaylib(tint));
}

} // namespace rui
