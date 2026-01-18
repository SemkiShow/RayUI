// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RWidgets/Layouts/RLayout.hpp"

class RHBoxLayout : public RLayout
{
  public:
    virtual ~RHBoxLayout() = default;

    void Shrink() override;
    void Update() override;
};
