// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RContainer.hpp"

class RScrollArea : public RContainer
{
  public:
    RScrollArea()
    {
        vBar.SetMaxWidth(barSize);
        vBar.SetThemeList(RThemeList::Secondary);
        hBar.SetMaxHeight(barSize);
        hBar.SetThemeList(RThemeList::Secondary);
        SetMargin(0);
    }
    virtual ~RScrollArea() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void SetScale(float scale) override;

    void SetBarSize(float val) { barSize = val; }

    float GetBarSize() { return barSize; }

    void SetBarRadius(float val) { barRadius = val; }

    float GetBarRadius() { return barRadius; }

    void SetBarSegments(int val) { barSegments = val; }

    int GetBarSegments() { return barSegments; }

    void SetEnabled(bool val) { enabled = val; }

    bool IsEnabled() { return enabled; }

    void SetWheelSensitivity(float val) { wheelSensitivity = val; }

    float GetWheelSensitivity() { return wheelSensitivity; }

  protected:
    float barSize = 10, barRadius = 3;
    int barSegments = 5;
    bool enabled = true;
    float wheelSensitivity = 20;

    void SetCentralWidgetsBounds() override;

  private:
    RVector2 lastMousePosition;
    RRectangle centralWidgetDrawBounds;
    RWidget vBar, hBar;
    bool vBarActive = false, hBarActive = false;
};
