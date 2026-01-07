// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RButton : public RWidget
{
  public:
    RButton() { maxSize.y = minSize.y; }
    RButton(float radius, int segments = 16) : RButton()
    {
        this->radius = radius;
        this->segments = segments;
    }
    virtual ~RButton() = default;

    void Draw() override;

    bool IsClicked() { return IsMouseLeftReleased(); }

  protected:
    float radius = 5;
    int segments = 16;
};
