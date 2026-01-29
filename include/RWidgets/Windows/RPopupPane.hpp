// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RPopupPane
 */

#pragma once

#include "RWidgets/Buttons/RIconButton.hpp"
#include "RWidgets/Panes/RPaneRounded.hpp"
#include "RWidgets/Windows/RWindow.hpp"

/**
 * @defgroup RWidget
 * @brief Widgets
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
