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
    RPane(RColor color = {127, 127, 127, 127}) : color(color) {}
    virtual ~RPane() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void SetColor(RColor col) { color = col; }

    RColor GetColor() { return color; }

    void SetLayout(std::shared_ptr<RLayout> val) { layout = val; }

  protected:
    RColor color;
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
