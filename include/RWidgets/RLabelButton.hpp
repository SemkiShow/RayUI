// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RLabelButton
 */

#pragma once

#include "RWidgets/RButton.hpp"

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

/**
 * @brief A traditional button with a label
 */
class RLabelButton : public RButton
{
  public:
    using RButton::RButton;
    RLabelButton(const std::string& label, float margin = 5) : margin(margin) { SetLabel(label); }
    virtual ~RLabelButton() = default;

    void Draw() override;

    void UpdateLabels() override;

    void SetLabel(const std::string& val)
    {
        labelId = val;
        UpdateLabels();
    }

    std::string GetLabel() { return label; }

    std::string GetLabelId() { return labelId; }

    void SetLabelAlign(RAlign val) { labelHAlign = val; }

    RAlign GetLabelAlign() { return labelHAlign; }

  protected:
    std::string label, labelId;
    RAlign labelHAlign = RAlign::HCenter;
    float margin = 5;
};
