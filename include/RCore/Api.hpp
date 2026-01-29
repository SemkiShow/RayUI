// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief A wrapper for some of raylib's functions
 */

#pragma once

#include "RCore/Utils.hpp"

namespace rui
{

/**
 * @defgroup Api
 * @{
 */

/**
 * @defgroup Window
 * @brief Get the dimensions of the window
 * @{
 */
float GetWindowWidth();
float GetWindowHeight();
RVector2 GetWindowSize();
/** @} */

/**
 * @defgroup Mouse
 * @brief Get the data from the mouse pointer
 * @{
 */
RVector2 GetMousePosition();
RVector2 GetMouseWheelMove();

bool IsMouseButtonPressed(RMouseButton button);
bool IsMouseButtonReleased(RMouseButton button);
bool IsMouseButtonDown(RMouseButton button);
bool IsMouseButtonUp(RMouseButton button);
/** @} */

/**
 * @defgroup Keys
 * @brief Get key events
 * @{
 */
bool IsKeyPressed(RKey key);
bool IsKeyReleased(RKey key);
bool IsKeyDown(RKey key);
bool IsKeyUp(RKey key);
/** @} */

/**
 * @defgroup UTF-8
 * @brief UTF-8 related functions
 * @{
 */

/**
 * @brief Converts a Unicode codepoint to a UTF-8 string
 * * @param codepoint The Unicode value to convert
 * @param[out] utf8Size Pointer to an integer where the byte length will be stored
 * * @return A pointer to a thread-local static buffer containing the UTF-8 string
 * * @warning The returned pointer is only valid until the next call to this function
 * If you need to keep the string, copy it immediately (e.g., to a std::string)
 */
const char* CodepointToUtf8(int codepoint, int* utf8Size);

/**
 * @brief Get the UTF-8 code of the last pressed key
 * Can be called multiple times to get all keys pressed between frames. If no keys remain the
 * function returns 0
 * @return The UTF-8 code of the last pressed key
 */
int GetCharPressed();

/**
 * @brief Decodes the next UTF-8 codepoint from a byte string
 * * This function is used to iterate through a UTF-8 string byte by byte. It decodes the current
 * character and tells you how many bytes to skip to reach the next one.
 * * @param text The current position in the UTF-8 string.
 * @param[out] codepointSize Pointer to an integer that will receive the number of bytes processed
 * * @return The integer Unicode codepoint (the actual character value).
 * * @note To iterate a full string, increment your pointer by the value
 * returned in @p codepointSize.
 * * @see CodepointToUtf8
 */
void GetCodepointNext(const char* text, int* codepointSize);
/** @} */

/**
 * @defgroup Drawing
 * @brief Drawing functions
 * @{
 */

void DrawRectangle(RRectangle rec, RColor color);
void DrawRectangleLines(RRectangle rec, float lineThickness, RColor color);

void DrawRectangleRounded(RRectangle rec, float roundness, int segments, RColor color);
void DrawRectangleRoundedLines(RRectangle rec, float roundness, int segments, float lineThickness,
                               RColor color);

void DrawCircle(RVector2 pos, float radius, RColor color);
void DrawCircleLines(RVector2 pos, float radius, float lineThickness, int segments, RColor color);

void DrawText(const std::string& text, RVector2 pos, float fontSize, RColor color);
void DrawTextFont(RFont font, const std::string& text, RVector2 pos, float fontSize, float spacing,
                  RColor color);

/**
 * @brief Measure the dimensions of text
 * New lines are counted and increase the height
 * @param text
 * @param fontSize
 * @return RVector2
 * @see MeasureTextFont
 */
RVector2 MeasureText(const std::string& text, float fontSize);

/**
 * @brief Measure the dimensions of text
 * New lines are counted and increase the height
 * @param font
 * @param text
 * @param fontSize
 * @param spacing font spacing
 * @return RVector2
 * @see MeasureText
 */
RVector2 MeasureTextFont(RFont font, const std::string& text, float fontSize, float spacing);

/**
 * @brief Limit drawing to the specified area
 * @note Works slightly differently to raylib's BeginScissorMode. When making nested calls the
 * function selects the minimum possible rectangle
 * @param rec
 */
void BeginScissorMode(RRectangle rec);
void EndScissorMode();

void DrawTexture(RTexture texture, RRectangle rec, RColor tint);
/** @} */

} // namespace rui
