// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RTextboxInt
 */

#pragma once

#include "RWidgets/RTextbox.hpp"
#include <cstdint>

/**
 * @defgroup Widgets
 * @{
 * @defgroup Textboxes
 * @{
 */

/**
 * @brief A textbox for integers
 */
class RTextboxInt : public RTextbox
{
  public:
    RTextboxInt(const std::string& promptText = "", int64_t number = 0)
    {
        this->promptText = promptText;
        SetNumber(number);
    }
    virtual ~RTextboxInt() = default;

    void Update() override;

    void SetNumber(int64_t val) { value = std::to_string(val); }

    int64_t GetNumber()
    {
        try
        {
            return std::stoll(value);
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }
};
