// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Layouts/RLayout.hpp"

class RHBoxLayout : public RLayout
{
  public:
    virtual ~RHBoxLayout() = default;

    void Update() override;
};
