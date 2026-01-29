// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RProgressBar
 */

#pragma once

#include "RCore/RWidget.hpp"

/**
 * @defgroup Widgets
 * @{
 * @defgroup ProgresBars
 * @{
 */

/**
 * @brief A progressbar
 */
class RProgressBar : public RWidget
{
  public:
    RProgressBar() { maxSize.y = minSize.y; }
    RProgressBar(float value, float minValue, float maxValue, float margin = 2) : RProgressBar()
    {
        this->value = value;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->margin = margin;
    }
    virtual ~RProgressBar() = default;

    void Draw() override;

    void SetValue(float val) { value = val; }

    float GetValue() { return value; }

    void SetMinValue(float val) { minValue = val; }

    float GetMinValue() { return minValue; }

    void SetMaxValue(float val) { maxValue = val; }

    float GetMaxValue() { return maxValue; }

    void SetMargin(float val) { margin = val; }

    float GetMargin() { return margin; }

    void SetRadius(float val) { radius = val; }

    float GetRadius() { return radius; }

    void SetSegments(int val) { segments = val; }

    int GetSegments() { return segments; }

  private:
    float value = 0, minValue = 0, maxValue = 1;
    float margin = 2;
    float radius = 5;
    int segments = 5;
};
