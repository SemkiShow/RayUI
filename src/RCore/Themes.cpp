// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/Themes.hpp"

RColor operator-(const RColor& a, const RColor& b)
{
    return {static_cast<unsigned char>(a.r - b.r), static_cast<unsigned char>(a.g - b.g),
            static_cast<unsigned char>(a.b - b.b), static_cast<unsigned char>((a.a + b.a) / 2)};
}

RColor operator*(const RColor& a, const float& b)
{
    return {static_cast<unsigned char>(a.r * b), static_cast<unsigned char>(a.g * b),
            static_cast<unsigned char>(a.b * b), a.a};
}

RColor operator/(const RColor& a, const float& b)
{
    return {static_cast<unsigned char>(a.r / b), static_cast<unsigned char>(a.g / b),
            static_cast<unsigned char>(a.b / b), a.a};
}

RThemeLight::RThemeLight()
{
    int primary = static_cast<int>(RThemeList::Primary);
    int secondary = static_cast<int>(RThemeList::Secondary);
    int border = static_cast<int>(RThemeList::Border);
    int text = static_cast<int>(RThemeList::Text);
    int background = static_cast<int>(RThemeList::Background);

    int defaultState = static_cast<int>(RThemeState::Default);
    int hovered = static_cast<int>(RThemeState::Hovered);
    int clicked = static_cast<int>(RThemeState::Clicked);
    int disabled = static_cast<int>(RThemeState::Disabled);
    int highlighted = static_cast<int>(RThemeState::Highlighted);

    hoveredTint = {"#7f7f7fff"};
    clickedTint = {"#ffffffff"};
    disabledTint = {"#000000ff"};
    highlightedTint = {"#7fb0ffff"};

    linkTint = {"#56adffff"};

    colors[primary][defaultState] = {"#dededeff"};
    colors[primary][hovered] = MixColors(colors[primary][defaultState], hoveredTint);
    colors[primary][clicked] = MixColors(colors[primary][defaultState], clickedTint);
    colors[primary][disabled] = MixColors(colors[primary][defaultState], disabledTint);
    colors[primary][highlighted] = MixColors(colors[primary][defaultState], highlightedTint);

    colors[secondary][defaultState] = {"#808080ff"};
    colors[secondary][hovered] = MixColors(colors[secondary][defaultState], hoveredTint);
    colors[secondary][clicked] = MixColors(colors[secondary][defaultState], clickedTint);
    colors[secondary][disabled] = MixColors(colors[secondary][defaultState], disabledTint);
    colors[secondary][highlighted] = MixColors(colors[secondary][defaultState], highlightedTint);

    colors[border][defaultState] = {"#999999ff"};
    colors[border][hovered] = MixColors(colors[border][hovered], hoveredTint);
    colors[border][clicked] = MixColors(colors[border][clicked], clickedTint);
    colors[border][disabled] = MixColors(colors[border][disabled], disabledTint);
    colors[border][highlighted] = MixColors(colors[border][highlighted], highlightedTint);

    colors[text][defaultState] = {"#000000ff"};
    colors[text][hovered] = MixColors(colors[text][defaultState], hoveredTint);
    colors[text][clicked] = MixColors(colors[text][defaultState], clickedTint);
    colors[text][disabled] = MixColors(colors[text][defaultState], disabledTint);
    colors[text][highlighted] = MixColors(colors[text][defaultState], highlightedTint);

    colors[background][defaultState] = {"#b0b0b0ff"};
    colors[background][hovered] = colors[background][defaultState];
    colors[background][clicked] = colors[background][defaultState];
    colors[background][disabled] = colors[background][defaultState];
    colors[background][highlighted] = colors[background][defaultState];
}

RThemeDark::RThemeDark()
{
    int primary = static_cast<int>(RThemeList::Primary);
    int secondary = static_cast<int>(RThemeList::Secondary);
    int border = static_cast<int>(RThemeList::Border);
    int text = static_cast<int>(RThemeList::Text);
    int background = static_cast<int>(RThemeList::Background);

    int defaultState = static_cast<int>(RThemeState::Default);
    int hovered = static_cast<int>(RThemeState::Hovered);
    int clicked = static_cast<int>(RThemeState::Clicked);
    int disabled = static_cast<int>(RThemeState::Disabled);
    int highlighted = static_cast<int>(RThemeState::Highlighted);

    // Invert colors of the light theme

    RThemeLight lightTheme;

    hoveredTint = lightTheme.hoveredTint;
    clickedTint = lightTheme.clickedTint;
    disabledTint = lightTheme.disabledTint;
    highlightedTint = lightTheme.highlightedTint;

    linkTint = lightTheme.linkTint;

    colors[primary][defaultState] = RColor{"#ffffff"} - lightTheme.colors[primary][defaultState];
    colors[primary][hovered] = RColor{"#ffffff"} - lightTheme.colors[primary][hovered];
    colors[primary][clicked] = RColor{"#ffffff"} - lightTheme.colors[primary][clicked];
    colors[primary][disabled] = RColor{"#ffffff"} - lightTheme.colors[primary][disabled];
    colors[primary][highlighted] = lightTheme.colors[primary][highlighted];

    colors[secondary][defaultState] =
        RColor{"#ffffff"} - lightTheme.colors[secondary][defaultState];
    colors[secondary][hovered] = RColor{"#ffffff"} - lightTheme.colors[secondary][hovered];
    colors[secondary][clicked] = RColor{"#ffffff"} - lightTheme.colors[secondary][clicked];
    colors[secondary][disabled] = RColor{"#ffffff"} - lightTheme.colors[secondary][disabled];
    colors[secondary][highlighted] = lightTheme.colors[secondary][highlighted];

    colors[border][defaultState] = RColor{"#ffffff"} - lightTheme.colors[border][defaultState];
    colors[border][hovered] = RColor{"#ffffff"} - lightTheme.colors[border][hovered];
    colors[border][clicked] = RColor{"#ffffff"} - lightTheme.colors[border][clicked];
    colors[border][disabled] = RColor{"#ffffff"} - lightTheme.colors[border][disabled];
    colors[border][highlighted] = lightTheme.colors[border][highlighted];

    colors[text][defaultState] = RColor{"#ffffff"} - lightTheme.colors[text][defaultState];
    colors[text][hovered] = RColor{"#ffffff"} - lightTheme.colors[text][hovered];
    colors[text][clicked] = RColor{"#ffffff"} - lightTheme.colors[text][clicked];
    colors[text][disabled] = RColor{"#ffffff"} - lightTheme.colors[text][disabled];
    colors[text][highlighted] = lightTheme.colors[text][highlighted];

    colors[background][defaultState] =
        RColor{"#ffffff"} - lightTheme.colors[background][defaultState];
    colors[background][hovered] = RColor{"#ffffff"} - lightTheme.colors[background][hovered];
    colors[background][clicked] = RColor{"#ffffff"} - lightTheme.colors[background][clicked];
    colors[background][disabled] = RColor{"#ffffff"} - lightTheme.colors[background][disabled];
    colors[background][highlighted] = lightTheme.colors[background][highlighted];
}

RColor GetThemeColor(RTheme theme, RThemeList themeList, RThemeState themeState)
{
    return theme.colors[static_cast<int>(themeList)][static_cast<int>(themeState)];
}
