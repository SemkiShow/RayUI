// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RWidget.hpp"
#include <functional>
#include <memory>

struct REvent
{
    std::weak_ptr<void> tracker;
    std::function<bool()> event;
    std::function<void()> func;

    REvent(std::weak_ptr<void> tracker, std::function<bool()> event, std::function<void()> func)
        : tracker(tracker), event(event), func(func)
    {
    }
};

class RWindow : public RWidget
{
  public:
    virtual ~RWindow() = default;

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

    void SetMargin(float val) { margin = val; }

    void SetCentralWidget(std::shared_ptr<RWidget> widget) { centralWidget = widget; }

    void UnsetCentralWidget() { centralWidget.reset(); }

    std::shared_ptr<RWidget> GetCentralWidget() { return centralWidget; }

    void Connect(std::shared_ptr<RWidget> tracker, std::function<bool()> event,
                 std::function<void()> func)
    {
        events.emplace_back(tracker, event, func);
    }

  protected:
    float margin = 10;
    std::shared_ptr<RWidget> centralWidget;
    std::vector<REvent> events;

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
