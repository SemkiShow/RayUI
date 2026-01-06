// SPDX-FileCopyrightfont: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RLabel : public RWidget
{
  public:
    RLabel() { Init(); }
    RLabel(const std::string& text, float fontSize = 24, float fontSpacing = 0) : RLabel()
    {
        this->text = text;
        this->fontSize = fontSize;
        this->fontSpacing = fontSpacing;
    }
    RLabel(const std::string& text, RColor tint, float fontSize = 24, float fontSpacing = 0)
        : RLabel()
    {
        this->text = text;
        this->fontSize = fontSize;
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
        fontSize = val;
        UpdateBounds();
    }

    float GetFontSize() { return fontSize; }

    void SetFontSpacing(float val)
    {
        fontSpacing = val;
        UpdateBounds();
    }

    float GetFontSpacing() { return fontSpacing; }

  protected:
    std::string text;
    float fontSize = 24, fontSpacing = 0;

    void Init() { themeList = RThemeList::Text; }
};
