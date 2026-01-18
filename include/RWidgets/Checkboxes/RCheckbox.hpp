// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RWidgets/Buttons/RIconButton.hpp"

class RCheckbox : public RIconButton
{
  public:
    RCheckbox() : RIconButton(RIcon::None) {}
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
