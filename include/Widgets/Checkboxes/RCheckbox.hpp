// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Buttons/RIconButton.hpp"

class RCheckbox : public RIconButton
{
  public:
    RCheckbox() : RIconButton(RIcon::None) {}
    virtual ~RCheckbox() = default;

    void Update() override;

    void SetChecked(bool val) { checked = val; }

    bool IsChecked() { return checked; }

  private:
    bool checked = false;
};
