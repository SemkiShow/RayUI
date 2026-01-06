// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Buttons/RButton.hpp"

class RLabelButton : public RButton
{
  public:
    using RButton::RButton;
    RLabelButton(const std::string& label, float margin = 5) : label(label), margin(margin) {}
    virtual ~RLabelButton() = default;

    void Draw() override;

    void SetLabel(const std::string& val) { label = val; }

    std::string GetLabel() { return label; }

    void SetLabelAlign(RAlign val) { labelHAlign = val; }

    RAlign GetLabelAlign() { return labelHAlign; }

  protected:
    std::string label;
    RAlign labelHAlign = RAlign::HCenter;
    float margin = 5;
};
