// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Containers/Layouts/RLayout.hpp"

class RVBoxLayout : public RLayout
{
  public:
    virtual ~RVBoxLayout() = default;

    void Update() override;
};
