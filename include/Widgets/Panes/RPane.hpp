// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
#include "Widgets/Layouts/RLayout.hpp"
#include <memory>

class RPane : public RWidget
{
  public:
    RPane()
    {
        themeList = RThemeList::Background;
        SetAnimated(false);
    }
    RPane(RColor tint) : RPane() { RWidget::SetTint(tint); }
    virtual ~RPane() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void UpdateLabels() override;

    void SetFont(std::shared_ptr<RFont> font) override;

    void SetTheme(std::shared_ptr<RTheme> theme) override;

    void SetScale(float scale) override;

    void SetLayout(std::shared_ptr<RLayout> val) { layout = val; }

  protected:
    std::shared_ptr<RLayout> layout;

    bool PollLayoutEvents()
    {
        if (layout && layout->IsVisible())
        {
            if (layout->PollEvents()) return true;
        }
        return false;
    }

    void DrawLayout()
    {
        if (layout && layout->IsVisible()) layout->Draw();
    }
};
