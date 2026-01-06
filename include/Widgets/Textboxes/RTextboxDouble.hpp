// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Textboxes/RTextbox.hpp"
#include <sstream>

class RTextboxDouble : public RTextbox
{
  public:
    RTextboxDouble(const std::string& promptText = "", double number = 0)
    {
        this->promptText = promptText;
        SetNumber(number);
    }
    virtual ~RTextboxDouble() = default;

    void Update() override;

    void SetNumber(double val)
    {
        std::stringstream ss;
        ss << val;
        text = ss.str();
    }

    double GetNumber()
    {
        try
        {
            return std::stod(text);
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }
};
