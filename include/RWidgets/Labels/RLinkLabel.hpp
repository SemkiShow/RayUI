// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RWidgets/Labels/RLabel.hpp"

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
