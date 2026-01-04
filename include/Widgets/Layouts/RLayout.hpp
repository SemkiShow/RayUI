// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
#include <memory>
#include <vector>

class RLayout : public RWidget
{
  public:
    virtual ~RLayout() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void SetPadding(float val) { padding = val; }
    void SetMargin(float val) { margin = val; }
    void AddWidget(std::shared_ptr<RWidget> widget) { widgets.push_back(widget); }

  protected:
    float padding = 5, margin = 10;
    std::vector<std::shared_ptr<RWidget>> widgets;

    bool PollWidgetsEvents()
    {
        for (int i = widgets.size() - 1; i >= 0; i--)
        {
            if (widgets[i]->IsVisible() && widgets[i]->PollEvents()) return true;
        }
        return false;
    }

    void UpdateWidgets()
    {
        for (auto& widget: widgets)
        {
            if (widget->IsVisible()) widget->Update();
        }
    }
};
