// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/Utils.hpp"
#include <array>

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
    RColor linkTint;
    std::array<std::array<RColor, R_THEME_STATE_SIZE>, R_THEME_LIST_SIZE> colors;
};

struct RThemeLight : public RTheme
{
    RThemeLight();
};

struct RThemeDark : public RTheme
{
    RThemeDark();
};

RColor GetThemeColor(RTheme theme, RThemeList themeList, RThemeState themeState);
