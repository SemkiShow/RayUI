// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RVBoxLayout
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RWidgets/Layouts/RLayout.hpp"

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
