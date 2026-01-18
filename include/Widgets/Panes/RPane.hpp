// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
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

    void SetDebugMode(bool val) override
    {
        if (centralWidget) centralWidget->SetDebugMode(val);
        debugMode = val;
    }

    void DrawDebugOutline() override;

    void SetFont(std::shared_ptr<RFont> font) override;

    void SetTheme(std::shared_ptr<RTheme> theme) override;

    void SetScale(float scale) override;

    void SetCentralWidget(std::shared_ptr<RWidget> widget) { centralWidget = widget; }

    void UnsetCentralWidget() { centralWidget.reset(); }

    std::shared_ptr<RWidget> GetCentralWidget() { return centralWidget; }

  protected:
    std::shared_ptr<RWidget> centralWidget;

    bool PollCentralWidgetEvents()
    {
        if (centralWidget && centralWidget->IsVisible())
        {
            if (centralWidget->PollEvents()) return true;
        }
        return false;
    }

    void DrawCentralWidget()
    {
        if (centralWidget && centralWidget->IsVisible()) centralWidget->Draw();
    }
};
