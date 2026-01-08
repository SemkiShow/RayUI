// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/Themes.hpp"
#include "Utils.hpp"
#include <memory>

namespace rui
{

float GetWindowWidth();
float GetWindowHeight();
RVector2 GetWindowSize();

RVector2 GetMousePosition();
bool IsMouseButtonPressed(RMouseButton button);
bool IsMouseButtonReleased(RMouseButton button);
bool IsMouseButtonDown(RMouseButton button);
bool IsMouseButtonUp(RMouseButton button);

bool IsKeyPressed(RKey key);
bool IsKeyReleased(RKey key);
bool IsKeyDown(RKey key);
bool IsKeyUp(RKey key);

const char* CodepointToUtf8(int codepoint, int* utf8Size);
int GetCharPressed();
void GetCodepointNext(const char* text, int* codepointSize);

void DrawRectangle(RRectangle rec, RColor color);
void DrawRectangleLines(RRectangle rec, float lineThickness, RColor color);
void DrawRectangleBorder(RRectangle rec, float borderThickness, RColor color, RTheme theme,
                         RThemeState themeState);

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color);
void DrawRectangleRoundedLines(RRectangle rec, float roundness, int segments, float lineThickness,
                               RColor color);
void DrawRectangleRoundedBorder(RRectangle rec, float roundness, int segments,
                                float borderThickness, RColor color, RTheme theme,
                                RThemeState themeState);

void DrawCircle(RVector2 pos, float radius, RColor color);
void DrawCircleLines(RVector2 pos, float radius, float lineThickness, int segments, RColor color);
void DrawCircleBorder(RVector2 pos, float radius, float borderThickness, int segments, RColor color,
                      RTheme theme, RThemeState themeState);

void DrawText(const std::string& text, RVector2 pos, float fontSize, RColor color);
void DrawTextFont(RFont font, const std::string& text, RVector2 pos, float fontSize, float spacing,
                  RColor color);
void DrawText(std::shared_ptr<RFont> font, const std::string& text, RVector2 pos, float fontSize,
              float spacing, RColor color);

RVector2 MeasureText(const std::string& text, float fontSize);
RVector2 MeasureTextFont(RFont font, const std::string& text, float fontSize, float spacing);
RVector2 MeasureText(std::shared_ptr<RFont> font, const std::string& text, float fontSize,
                     float spacing);

void BeginScissorMode(RRectangle rec);
void EndScissorMode();

} // namespace rui
