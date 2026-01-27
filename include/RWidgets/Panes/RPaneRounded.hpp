// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RPaneRounded
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RWidgets/Panes/RPane.hpp"

/**
 * @brief A rounded version of RPane
 */
class RPaneRounded : public RPane
{
  public:
    using RPane::RPane;
    RPaneRounded(float radius = 20, int segments = 16) : radius(radius), segments(segments) {}
    virtual ~RPaneRounded() = default;

    void Draw() override;

    void SetRadius(float val) { radius = val; }

    float GetRadius() { return radius; }

    void SetSegments(int val) { segments = val; }

    int GetSegments() { return segments; }

  protected:
    float radius = 20;
    int segments = 5;
};
