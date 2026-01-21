// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RWidget.hpp"
#include <functional>
#include <memory>

struct REvent
{
    std::vector<std::weak_ptr<void>> dependencies;
    std::function<bool()> event;
    std::function<void()> func;

    bool IsValid() const
    {
        if (!event || !func) return false;
        for (auto& dep: dependencies)
        {
            if (dep.expired()) return false;
        }
        return true;
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

    void SetMargin(float val)
    {
        margin = val;
        UpdateBounds();
    }

    void SetCentralWidget(std::shared_ptr<RWidget> widget)
    {
        centralWidget = widget;
        UpdateBounds();
    }

    void UnsetCentralWidget()
    {
        centralWidget.reset();
        UpdateBounds();
    }

    std::shared_ptr<RWidget> GetCentralWidget() { return centralWidget; }

    template <typename... Tracker>
    void Connect(std::function<bool()> event, std::function<void()> func,
                 std::shared_ptr<Tracker>... deps)
    {
        REvent e;
        e.event = event;
        e.func = func;
        (e.dependencies.push_back(deps), ...);
        events.push_back(std::move(e));
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

    void UpdateEvents()
    {
        std::vector<std::function<void()>> actionsToRun;

        for (auto it = events.begin(); it != events.end();)
        {
            if (!it->IsValid())
            {
                it = events.erase(it);
                continue;
            }

            if (it->event && it->event())
            {
                actionsToRun.push_back(it->func);
            }
            ++it;
        }

        for (const auto& action: actionsToRun)
        {
            action();
        }
    }
};
