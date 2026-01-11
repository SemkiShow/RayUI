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
    RLabel(const std::string& label, float fontSize = 24, float fontSpacing = 0) : RLabel()
    {
        this->labelId = label;
        UpdateLabels();
        this->maxSize.y = fontSize;
        this->fontSpacing = fontSpacing;
    }
    RLabel(const std::string& label, RColor tint, float fontSize = 24, float fontSpacing = 0)
        : RLabel()
    {
        this->labelId = label;
        UpdateLabels();
        this->maxSize.y = fontSize;
        this->fontSpacing = fontSpacing;
        RWidget::SetTint(tint);
    }
    virtual ~RLabel() = default;

    void Shrink() override;
    void Draw() override;

    void UpdateLabels() override;

    void SetLabel(const std::string& val)
    {
        labelId = val;
        UpdateLabels();
        UpdateBounds();
    }

    std::string GetLabel() { return label; }

    std::string GetLabelId() { return labelId; }

    void SetFontSize(float val)
    {
        maxSize.y = val;
        UpdateBounds();
    }

    float GetFontSize() { return maxSize.y; }

  protected:
    std::string label, labelId;
};
