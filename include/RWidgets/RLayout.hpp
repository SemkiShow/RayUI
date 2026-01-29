// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RLayout
 */

#pragma once

#include "RCore/RWidget.hpp"
#include <memory>
#include <vector>

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

/**
 * @brief A generic layout that does not position widgets
 */
class RLayout : public RWidget
{
  public:
    virtual ~RLayout() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void UpdateLabels() override;

    void SetDebugMode(bool val) override
    {
        for (auto& widget: widgets) widget->SetDebugMode(val);
        debugMode = val;
    }

    void DrawDebugOutline() override;

    void SetFont(std::shared_ptr<RFont> font) override;

    void SetTheme(std::shared_ptr<RTheme> theme) override;

    void SetScale(float scale) override;

    void SetPadding(float val)
    {
        padding = val;
        UpdateBounds();
    }

    float GetPadding() { return padding; }

    void SetMargin(float val)
    {
        margin = val;
        UpdateBounds();
    }

    float GetMargin() { return margin; }

    void AddWidget(std::shared_ptr<RWidget> widget)
    {
        widgets.push_back(widget);
        UpdateBounds();
    }

    void InsertWidget(size_t idx, std::shared_ptr<RWidget> widget)
    {
        if (idx > widgets.size()) throw std::runtime_error("Invalid idx in InsertWidget!");
        widgets.insert(widgets.begin() + idx, widget);
        UpdateBounds();
    }

    void EraseWidget(size_t idx)
    {
        if (idx >= widgets.size()) throw std::runtime_error("Invalid idx in EraseWidget!");
        widgets.erase(widgets.begin() + idx);
        UpdateBounds();
    }

    void PopBack()
    {
        if (widgets.empty()) throw std::runtime_error("PopBack is called on an empty RLayout!");
        widgets.pop_back();
        UpdateBounds();
    }

    void ClearWidgets()
    {
        widgets.clear();
        UpdateBounds();
    }

    std::shared_ptr<RWidget> GetWidget(size_t idx)
    {
        if (idx >= widgets.size()) throw std::runtime_error("Invalid idx in GetWidget!");
        return widgets[idx];
    }

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

    void CleanupWidgets()
    {
        for (auto it = widgets.begin(); it != widgets.end();)
        {
            if ((*it)->IsDeleteLater())
            {
                it = widgets.erase(it);
                continue;
            }
            ++it;
        }
    }
};
