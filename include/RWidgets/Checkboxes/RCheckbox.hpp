// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RCheckbox
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RWidgets/Buttons/RIconButton.hpp"

/**
 * @brief A checkbox
 */
class RCheckbox : public RIconButton
{
  public:
    RCheckbox(bool value = false) : RIconButton(RIcon::None) { SetValue(value); }
    virtual ~RCheckbox() = default;

    void Update() override;

    void SetValue(bool val)
    {
        value = val;
        icon = (value ? RIcon::Cross : RIcon::None);
    }

    bool GetValue() { return value; }

  private:
    bool value = false;
};
