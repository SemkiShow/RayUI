// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Panes/RPane.hpp"

class RPaneRounded : public RPane
{
  public:
    using RPane::RPane;
    RPaneRounded(float roundness = 0.1f, int segments = 16)
        : roundness(roundness), segments(segments)
    {
    }
    virtual ~RPaneRounded() = default;

    void Draw() override;

    void SetRoundness(float val) { roundness = val; }
    void SetSegments(int val) { segments = val; }

    float GetRoundness() { return roundness; }
    int GetSegments() { return segments; }

  protected:
    float roundness;
    int segments;
};
