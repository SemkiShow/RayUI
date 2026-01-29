// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RIconButton
 */

#pragma once

#include "RCore/Icons.hpp"
#include "RWidgets/RButton.hpp"

/**
 * @defgroup Widgets
 * @{
 * @defgroup Buttons
 * @{
 */

/**
 * @brief A button with an RIcon instead of a label
 */
class RIconButton : public RButton
{
  public:
    RIconButton(RIcon icon) : icon(icon)
    {
        maxSize.x = minSize.x;
        maxSize.y = minSize.y;
    }
    virtual ~RIconButton() = default;

    void Draw() override;

    void SetIcon(RIcon val) { icon = val; }

    RIcon GetIcon() { return icon; }

  protected:
    RIcon icon;
};
