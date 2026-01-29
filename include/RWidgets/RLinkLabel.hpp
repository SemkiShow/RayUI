// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RLinkLabel
 */

#pragma once

#include "RWidgets/RLabel.hpp"

/**
 * @defgroup Widgets
 * @{
 * @defgroup Labels
 * @{
 */

/**
 * @brief A link label
 * @warning It is not safe to use with user input
 */
class RLinkLabel : public RLabel
{
  public:
    using RLabel::RLabel;
    RLinkLabel() { SetTint(GetTheme()->linkTint); }
    RLinkLabel(const std::string& label, const std::string& link) : RLinkLabel()
    {
        this->labelId = label;
        UpdateLabels();
        this->link = link;
    }
    virtual ~RLinkLabel() = default;

    void Update() override;

    void SetTheme(std::shared_ptr<RTheme> val) override
    {
        theme = val;
        SetTint(GetTheme()->linkTint);
    }

  protected:
    std::string link;
};
