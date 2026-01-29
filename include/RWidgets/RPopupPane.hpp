// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RPopupPane
 */

#pragma once

#include "RWidgets/RIconButton.hpp"
#include "RWidgets/RPaneRounded.hpp"
#include "RWidgets/RWindow.hpp"

/**
 * @defgroup Widgets
 * @{
 * @defgroup Windows
 * @{
 */

/**
 * @brief A non-draggable RWindow with an RPaneRounded as the background
 */
class RPopupPane : public RWindow
{
  public:
    RPopupPane() : closeButton(RIcon::Cross) {}
    virtual ~RPopupPane() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    bool IsCloseButtonClicked() { return closeButton.IsClicked(); }

    void SetPaneMargin(float val) { paneMargin = val; }

    float GetPaneMargin() { return paneMargin; }

  protected:
    float paneMargin = 10;

  private:
    RIconButton closeButton;
    RPaneRounded pane;
};
