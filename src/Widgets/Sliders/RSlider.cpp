// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Sliders/RSlider.hpp"
#include "Api.hpp"

template <typename T>
void RBaseSlider<T>::CheckSelected()
{
    if (IsMouseLeftPressed())
    {
        selected = true;
    }
    if (rui::IsMouseButtonReleased(RMouseButton::Left))
    {
        selected = false;
    }
}

template <typename T>
void RBaseSlider<T>::UpdateRegular()
{
    RVector2 textSize;
    if (font)
        textSize = rui::MeasureTextFont(*font, GetMaxValueString(), bounds.height, fontSpacing);
    else
        textSize = rui::MeasureText(GetMaxValueString(), bounds.height);

    RRectangle recBounds = {
        bounds.x + bounds.height / 2, bounds.y + bounds.height * (1 - recHeightPercent) / 2,
        bounds.width - bounds.height - padding - textSize.x, bounds.height * recHeightPercent};

    RVector2 mouse = rui::GetMousePosition();

    value = Map(mouse.x, recBounds.x, recBounds.x + recBounds.width, minValue, maxValue);
}

template <typename T>
void RBaseSlider<T>::UpdateRectangle()
{
    RRectangle sliderBounds = {bounds.x + borderThickness, bounds.y + borderThickness,
                               bounds.width - borderThickness * 2 - sliderWidth,
                               bounds.height - borderThickness * 2};

    RVector2 mouse = rui::GetMousePosition();

    value = Map(mouse.x - sliderWidth / 2, sliderBounds.x, sliderBounds.x + sliderBounds.width,
                minValue, maxValue);
}

template <typename T>
void RBaseSlider<T>::Update()
{
    RWidget::Update();
    RBaseSlider::CheckSelected();

    if (selected)
    {
        if (type == RSliderType::Regular) UpdateRegular();
        if (type == RSliderType::Rectangle) UpdateRectangle();
    }
}

template <typename T>
void RBaseSlider<T>::DrawRegular()
{
    RVector2 textSize;
    if (font)
        textSize = rui::MeasureTextFont(*font, GetMaxValueString(), bounds.height, fontSpacing);
    else
        textSize = rui::MeasureText(GetMaxValueString(), bounds.height);

    RRectangle recBounds = {
        bounds.x + bounds.height / 2, bounds.y + bounds.height * (1 - recHeightPercent) / 2,
        bounds.width - bounds.height - padding - textSize.x, bounds.height * recHeightPercent};
    rui::DrawRectangleRounded(recBounds, 1, recBounds.height, color);
    rui::DrawRectangleRoundedLines(recBounds, 1, recBounds.height, borderThickness,
                                   GetThemeColor(RThemeList::Border, themeState));

    RVector2 circlePos;
    circlePos.x = Map(value, minValue, maxValue, recBounds.x, recBounds.x + recBounds.width);
    circlePos.y = recBounds.y + recBounds.height / 2;
    rui::DrawCircle(circlePos, bounds.height / 2, color);
    rui::DrawCircleLines(circlePos, bounds.height / 2, borderThickness, segments,
                         GetThemeColor(RThemeList::Border, themeState));

    RVector2 textPos{recBounds.x + recBounds.width + bounds.height / 2 + padding, bounds.y};
    if (font)
        rui::DrawTextFont(*font, GetValueString(), textPos, bounds.height, fontSpacing,
                          GetThemeColor(RThemeList::Text, themeState));
    else
        rui::DrawText(GetValueString(), textPos, bounds.height,
                      GetThemeColor(RThemeList::Text, themeState));
}

template <typename T>
void RBaseSlider<T>::DrawRectangle()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRounded(bounds, roundness, bounds.height, color);
    rui::DrawRectangleRoundedLines(bounds, roundness, bounds.height, borderThickness,
                                   GetThemeColor(RThemeList::Border, themeState));

    RVector2 sliderPos;
    sliderPos.x = Map(value, minValue, maxValue, bounds.x + borderThickness,
                      bounds.x + bounds.width - borderThickness - sliderWidth);
    sliderPos.y = bounds.y + borderThickness;
    rui::DrawRectangle({sliderPos.x, sliderPos.y, sliderWidth, bounds.height - borderThickness * 2},
                       GetThemeColor(RThemeList::Secondary, themeState));

    RVector2 textSize;
    if (font)
        textSize = rui::MeasureTextFont(*font, GetMaxValueString(), bounds.height, fontSpacing);
    else
        textSize = rui::MeasureText(GetMaxValueString(), bounds.height);

    RVector2 textPos{bounds.x + (bounds.width - textSize.x) / 2, bounds.y + margin};
    if (font)
        rui::DrawTextFont(*font, GetValueString(), textPos, bounds.height - 2 * margin, fontSpacing,
                          GetThemeColor(RThemeList::Text, themeState));
    else
        rui::DrawText(GetValueString(), textPos, bounds.height - 2 * margin,
                      GetThemeColor(RThemeList::Text, themeState));
}

template <typename T>
void RBaseSlider<T>::Draw()
{
    if (type == RSliderType::Regular) DrawRegular();
    if (type == RSliderType::Rectangle) DrawRectangle();
}

template class RBaseSlider<float>;
template class RBaseSlider<int>;
