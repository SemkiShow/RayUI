// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RBar : public RWidget
{
  public:
    RBar() { Init(); }
    RBar(float thickness) : thickness(thickness) { Init(); }
    RBar(RColor tint) : RBar() { RWidget::SetTint(tint); }
    ~RBar() = default;

    void Draw() override;

    void SetThickness(float val) { maxSize.y = thickness = val; }

    float GetThickness() { return thickness; }

  protected:
    float thickness = 1;

  private:
    void Init() { maxSize.y = thickness; }
};
