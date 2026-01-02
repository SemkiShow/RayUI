// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RPane : public RWidget
{
  public:
    RPane(RColor color = {127, 127, 127, 127}) : color(color) {}
    virtual ~RPane() = default;

    void Draw() override;

  protected:
    RColor color;
};
