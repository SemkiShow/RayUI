// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Labels/RLabel.hpp"

class RLinkLabel : public RLabel
{
  public:
    using RLabel::RLabel;
    RLinkLabel() { Init(); }
    RLinkLabel(const std::string& text, const std::string& link) : RLinkLabel()
    {
        this->text = text;
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

  private:
    void Init() { SetTint(GetTheme()->linkTint); }
};
