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
    RRectangle recBounds = {bounds.x + bounds.height / 2,
                            bounds.y + bounds.height * (1 - recHeightPercent) / 2,
                            bounds.width - bounds.height, bounds.height * recHeightPercent};

    if (showValue)
    {
        RVector2 textSize = rui::MeasureText(font, GetMaxValueString(), bounds.height, fontSpacing);
        recBounds.width -= padding + textSize.x;
    }

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
        valueChanged = rui::GetMousePosition() != lastMousePosition;
        lastMousePosition = rui::GetMousePosition();

        if (type == RSliderType::Regular) UpdateRegular();
        if (type == RSliderType::Rectangle) UpdateRectangle();
    }
}

template <typename T>
void RBaseSlider<T>::DrawRegular()
{

    RRectangle recBounds = {bounds.x + bounds.height / 2,
                            bounds.y + bounds.height * (1 - recHeightPercent) / 2,
                            bounds.width - bounds.height, bounds.height * recHeightPercent};
    if (showValue)
    {
        RVector2 textSize = rui::MeasureText(font, GetMaxValueString(), bounds.height, fontSpacing);
        recBounds.width -= padding + textSize.x;
    }
    rui::DrawRectangleRoundedBorder(recBounds, 1, recBounds.height, borderThickness, color, *theme,
                                    themeState);

    RVector2 circlePos;
    circlePos.x = Map(value, minValue, maxValue, recBounds.x, recBounds.x + recBounds.width);
    circlePos.y = recBounds.y + recBounds.height / 2;

    RRectangle highlightBounds = {recBounds.x, recBounds.y, circlePos.x - recBounds.x,
                                  recBounds.height};
    rui::DrawRectangleRoundedBorder(highlightBounds, 1, segments, borderThickness,
                                    GetThemeColor(themeList, RThemeState::Highlighted), *theme,
                                    themeState);

    rui::DrawCircleBorder(circlePos, bounds.height / 2, borderThickness, segments,
                          GetThemeColor(RThemeList::Secondary, themeState), *theme, themeState);

    if (showValue)
    {
        RVector2 textPos{recBounds.x + recBounds.width + bounds.height / 2 + padding, bounds.y};
        rui::DrawText(font, GetValueString(), textPos, bounds.height, fontSpacing,
                      GetThemeColor(RThemeList::Text, themeState));
    }
}

template <typename T>
void RBaseSlider<T>::DrawRectangle()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, bounds.height, borderThickness, color,
                                    *theme, themeState);

    RVector2 sliderPos;
    sliderPos.x = Map(value, minValue, maxValue, bounds.x + borderThickness,
                      bounds.x + bounds.width - borderThickness - sliderWidth);
    sliderPos.y = bounds.y + borderThickness;

    RRectangle highlightBounds = {bounds.x, bounds.y, sliderPos.x - bounds.x + sliderWidth,
                                  bounds.height};
    rui::DrawRectangleRoundedBorder(highlightBounds, roundness, segments, borderThickness,
                                    GetThemeColor(themeList, RThemeState::Highlighted), *theme,
                                    themeState);

    rui::DrawRectangleRoundedBorder(
        {sliderPos.x, sliderPos.y, sliderWidth, bounds.height - borderThickness * 2}, roundness,
        segments, borderThickness, GetThemeColor(RThemeList::Secondary, themeState), *theme,
        themeState);

    if (showValue)
    {
        RVector2 textSize = rui::MeasureText(font, GetMaxValueString(), bounds.height, fontSpacing);

        RVector2 textPos{bounds.x + (bounds.width - textSize.x) / 2, bounds.y + margin};
        rui::DrawText(font, GetValueString(), textPos, bounds.height - 2 * margin, fontSpacing,
                      GetThemeColor(RThemeList::Text, themeState));
    }
}

template <typename T>
void RBaseSlider<T>::Draw()
{
    if (type == RSliderType::Regular) DrawRegular();
    if (type == RSliderType::Rectangle) DrawRectangle();
}

template class RBaseSlider<float>;
template class RBaseSlider<int>;
