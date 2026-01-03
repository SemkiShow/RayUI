// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
#include <memory>

class RWindow : public RWidget
{
  public:
    virtual ~RWindow() = default;

    void Update() override;
    void Draw() override;

    void SetMargin(float val) { margin = val; }
    void SetCentralWidget(std::shared_ptr<RWidget> widget) { centralWidget = widget; }

  protected:
    float margin = 10;
    std::shared_ptr<RWidget> centralWidget;

    void DrawCentralWidget()
    {
        if (centralWidget && centralWidget->IsVisible()) centralWidget->Draw();
    }
};
