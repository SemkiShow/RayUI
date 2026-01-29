// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RVBoxLayout
 */

#pragma once

#include "RWidgets/RLayout.hpp"

/**
 * @defgroup Widgets
 * @{
 * @defgroup Layouts
 * @{
 */

/**
 * @brief A layout for aligning widgets vertically
 */
class RVBoxLayout : public RLayout
{
  public:
    virtual ~RVBoxLayout() = default;

    void Shrink() override;
    void Update() override;
};
