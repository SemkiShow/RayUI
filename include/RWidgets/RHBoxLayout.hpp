// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RHBoxLayout
 */

#pragma once

#include "RWidgets/RLayout.hpp"

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

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
