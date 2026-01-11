// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Textboxes/RTextbox.hpp"

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
