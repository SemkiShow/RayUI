// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RTextboxDouble
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RWidgets/Textboxes/RTextbox.hpp"
#include <sstream>

/**
 * @brief A textbox for real numbers
 */
class RTextboxDouble : public RTextbox
{
  public:
    RTextboxDouble(const std::string& promptText = "", double number = 0)
    {
        this->promptTextId = promptText;
        SetNumber(number);
    }
    virtual ~RTextboxDouble() = default;

    void Update() override;

    void SetNumber(double val)
    {
        std::stringstream ss;
        ss << val;
        value = ss.str();
    }

    double GetNumber()
    {
        try
        {
            return std::stod(value);
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }
};
