// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RWidget.hpp"

class RContainer : public RWidget
{
  public:
    virtual ~RContainer() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void UpdateLabels() override;
    void SetDebugMode(bool val) override;
    void DrawDebugOutline() override;
    void SetFont(std::shared_ptr<RFont> font) override;
    void SetTheme(std::shared_ptr<RTheme> theme) override;
    void SetScale(float scale) override;

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

    void SetMargin(float val)
    {
        margin = val;
        UpdateBounds();
    }

    float GetMargin() { return margin; }

  protected:
    std::shared_ptr<RWidget> centralWidget;
    float margin = 10;

    bool PollCentralWidgetEvents()
    {
        if (centralWidget && centralWidget->IsVisible())
        {
            if (centralWidget->PollEvents()) return true;
        }
        return false;
    }

    virtual void SetCentralWidgetsBounds()
    {
        if (centralWidget)
        {
            centralWidget->SetBounds(AddMargin(bounds, margin));
            centralWidget->UpdateBounds();
        }
    }

    void DrawCentralWidget()
    {
        if (centralWidget && centralWidget->IsVisible()) centralWidget->Draw();
    }
};
