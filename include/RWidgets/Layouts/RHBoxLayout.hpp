// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RHBoxLayout
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RWidgets/Layouts/RLayout.hpp"

/**
 * @brief A layout for aligning widgets horizontally
 */
class RHBoxLayout : public RLayout
{
  public:
    virtual ~RHBoxLayout() = default;

    void Shrink() override;
    void Update() override;
};
