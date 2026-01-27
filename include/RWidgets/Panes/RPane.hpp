// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RPane
 */

#pragma once

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#include "RCore/RContainer.hpp"

/**
 * @brief A background pane
 */
class RPane : public RContainer
{
  public:
    RPane()
    {
        themeList = RThemeList::Background;
        SetAnimated(false);
        SetMargin(0);
    }
    RPane(RColor tint) : RPane() { RWidget::SetTint(tint); }
    virtual ~RPane() = default;

    void Draw() override;
};
