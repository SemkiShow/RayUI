// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RBar : public RWidget
{
  public:
    RBar(float thickness = 1, RColor color = {127, 127, 127}) : thickness(thickness), color(color)
    {
        maxSize.y = thickness;
    }
    ~RBar() = default;

    void Draw() override;

    void SetThickness(float val) { maxSize.y = thickness = val; }

    float GetThickness() { return thickness; }

  protected:
    float thickness;
    RColor color;
};
