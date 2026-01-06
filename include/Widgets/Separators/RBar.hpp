// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RBar : public RWidget
{
  public:
    RBar() { Init(); }
    RBar(float thickness) { maxSize.y = thickness; }
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

  private:
    void Init() { maxSize.y = 1; }
};
