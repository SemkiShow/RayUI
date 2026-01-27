// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RBar
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RCore/RWidget.hpp"

/**
 * @brief \<hr>
 */
class RBar : public RWidget
{
  public:
    RBar() { maxSize.y = 1; }
    RBar(float thickness) : RBar() { maxSize.y = thickness; }
    RBar(RColor tint) : RBar() { RWidget::SetTint(tint); }
    ~RBar() = default;

    void Draw() override;

    void SetScale(float val) override
    {
        float delta = val / scale;
        if (maxSize.y >= 0) maxSize.y /= delta;
        RWidget::SetScale(val);
    }

    void SetThickness(float val) { maxSize.y = val; }

    float GetThickness() { return maxSize.y; }
};
