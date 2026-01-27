// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief Themes
 */

#pragma once

#include "RCore/Utils.hpp"
#include <array>

/**
 * @brief A group for colors
 */
enum class RThemeList
{
    Primary,
    Secondary,
    Border,
    Text,
    Background
};
constexpr size_t R_THEME_LIST_SIZE = 5;

/**
 * @brief A state of the widget
 */
enum class RThemeState
{
    Default,
    Hovered,
    Clicked,
    Disabled,
    Highlighted
};
constexpr size_t R_THEME_STATE_SIZE = 5;

/**
 * @brief A generic theme struct
 */
struct RTheme
{
    RColor hoveredTint, clickedTint, disabledTint, highlightedTint;
    RColor linkTint;
    std::array<std::array<RColor, R_THEME_STATE_SIZE>, R_THEME_LIST_SIZE> colors;
};

/**
 * @brief The light theme
 */
struct RThemeLight : public RTheme
{
    RThemeLight();
};

/**
 * @brief The dark theme
 */
struct RThemeDark : public RTheme
{
    RThemeDark();
};

/**
 * @brief Extract a color from a theme
 *
 * @param theme
 * @param themeList
 * @param themeState
 * @return RColor
 */
RColor GetThemeColor(RTheme theme, RThemeList themeList, RThemeState themeState);
