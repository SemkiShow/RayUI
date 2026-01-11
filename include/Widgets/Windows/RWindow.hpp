// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
#include <functional>
#include <memory>

class RWindow : public RWidget
{
  public:
    virtual ~RWindow() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void UpdateLabels() override;

    void SetFont(std::shared_ptr<RFont> font) override;

    void SetTheme(std::shared_ptr<RTheme> theme) override;

    void SetScale(float scale) override;

    void SetMargin(float val) { margin = val; }
    void SetCentralWidget(std::shared_ptr<RWidget> widget) { centralWidget = widget; }

    void Connect(std::function<bool()> event, std::function<void()> func)
    {
        events.emplace_back(event, func);
    }

  protected:
    float margin = 10;
    std::shared_ptr<RWidget> centralWidget;
    std::vector<std::pair<std::function<bool()>, std::function<void()>>> events;

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
