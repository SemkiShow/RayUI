// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RGridLayout
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
 * @brief A layout positioning widgets in a grid
 * @note Widget alignment aligns them in their cell
 */
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
