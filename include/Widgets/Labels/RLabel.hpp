// SPDX-FileCopyrightfont: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RLabel : public RWidget
{
  public:
    RLabel()
    {
        themeList = RThemeList::Text;
        maxSize.y = 24;
    }
    RLabel(const std::string& text, float fontSize = 24, float fontSpacing = 0) : RLabel()
    {
        this->text = text;
        this->maxSize.y = fontSize;
        this->fontSpacing = fontSpacing;
    }
    RLabel(const std::string& text, RColor tint, float fontSize = 24, float fontSpacing = 0)
        : RLabel()
    {
        this->text = text;
        this->maxSize.y = fontSize;
        this->fontSpacing = fontSpacing;
        RWidget::SetTint(tint);
    }
    virtual ~RLabel() = default;

    void Shrink() override;
    void Draw() override;

    void SetText(const std::string& val)
    {
        text = val;
        UpdateBounds();
    }

    std::string GetText() { return text; }

    void SetFontSize(float val)
    {
        maxSize.y = val;
        UpdateBounds();
    }

    float GetFontSize() { return maxSize.y; }

  protected:
    std::string text;
};
