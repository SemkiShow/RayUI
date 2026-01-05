// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Layouts/RLayout.hpp"

class RVBoxLayout : public RLayout
{
  public:
    virtual ~RVBoxLayout() = default;

    void Shrink() override;
    void Update() override;
};
