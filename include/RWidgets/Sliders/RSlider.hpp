// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RWidget.hpp"
#include <iomanip>
#include <sstream>

enum class RSliderType
{
    Regular,
    Rectangle
};

template <typename T>
class RBaseSlider : public RWidget
{
  public:
    RBaseSlider() { maxSize.y = minSize.y; }
    RBaseSlider(T value, T minValue, T maxValue, RSliderType type = RSliderType::Regular)
        : RBaseSlider()
    {
        this->value = value;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->type = type;
    }
    virtual ~RBaseSlider() = default;

    void Update() override;
    void Draw() override;

    void SetValue(T val) { value = val; }

    T GetValue() { return value; }

    std::string GetValueString()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << value;
        return ss.str();
    }

    void SetMinValue(T val) { minValue = val; }

    T GetMinValue() { return minValue; }

    std::string GetMinValueString()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << minValue;
        return ss.str();
    }

    void SetMaxValue(T val) { maxValue = val; }

    T GetMaxValue() { return maxValue; }

    std::string GetMaxValueString()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << maxValue;
        return ss.str();
    }

    void SetSegments(int val) { segments = val; }

    int GetSegments() { return segments; }

    void SetType(RSliderType val) { type = val; }

    RSliderType GetType() { return type; }

    void SetShowValue(bool val) { showValue = val; }

    bool IsShowValue() { return showValue; }

    void SetRecHeightPercent(float val) { recHeightPercent = val; }

    float GetRecHeightPercent() { return recHeightPercent; }

    void SetPadding(float val) { padding = val; }

    float GetPadding() { return padding; }

    void SetRadius(float val) { radius = val; }

    float GetRadius() { return radius; }

    void SetSliderWidth(float val) { sliderWidth = val; }

    float GetSliderWidth() { return sliderWidth; }

    void SetMarging(float val) { margin = val; }

    float GetMargin() { return margin; }

    bool IsSelected() { return selected; }
    bool IsValueChanged() { return valueChanged; }

  protected:
    T value = 0, minValue = 0, maxValue = 1;
    int segments = 16;
    RSliderType type = RSliderType::Regular;
    float showValue = true;

    // RSliderType::Regular
    float recHeightPercent = 0.25f;
    float padding = 5;

    // RSliderType::Rectangle
    float radius = 5;
    float sliderWidth = 10;
    float margin = 5;

    void CheckSelected();

    void UpdateRegular();
    void UpdateRectangle();

    void DrawRegular();
    void DrawRectangle();

  private:
    bool selected = false, valueChanged = false;
    RVector2 lastMousePosition;
};

using RSlider = RBaseSlider<float>;
using RSliderInt = RBaseSlider<int>;
