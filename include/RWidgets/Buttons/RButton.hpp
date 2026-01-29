// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RButton
 */

#pragma once

#include "RCore/RWidget.hpp"

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

/**
 * @brief A generic button with no label
 */
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

    void Update() override;
    void Draw() override;

    void SetRadius(float val) { radius = val; }
    void SetSegments(int val) { segments = val; }

    float GetRadius() { return radius; }
    int GetSegments() { return segments; }

    bool IsClicked() { return IsMouseLeftReleased() && wasSelected; }

  protected:
    float radius = 5;
    int segments = 5;

  private:
    bool selected = false, wasSelected = false;
};
