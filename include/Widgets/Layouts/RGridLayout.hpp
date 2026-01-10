// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Layouts/RLayout.hpp"

class RGridLayout : public RLayout
{
  public:
    RGridLayout(int columns) : columns(columns) {}
    virtual ~RGridLayout() = default;

    void Shrink() override;
    void Update() override;

  protected:
    int columns = 1;
};
