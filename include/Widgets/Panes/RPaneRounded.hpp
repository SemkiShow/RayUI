// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Panes/RPane.hpp"

class RPaneRounded : public RPane
{
  public:
    using RPane::RPane;
    RPaneRounded(float radius = 20, int segments = 16) : radius(radius), segments(segments) {}
    virtual ~RPaneRounded() = default;

    void Draw() override;

    void SetRadius(float val) { radius = val; }
    void SetSegments(int val) { segments = val; }

    float GetRadius() { return radius; }
    int GetSegments() { return segments; }

  protected:
    float radius;
    int segments;
};
