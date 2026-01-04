// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Layouts/RLayout.hpp"

class RHBoxLayout : public RLayout
{
  public:
    virtual ~RHBoxLayout() = default;

    void ShrinkToContent() override;
    void Update() override;

  protected:
    void SetWidgetPositions()
    {
        float posX = GetPositionX() + margin;
        for (auto& widget: widgets)
        {
            widget->SetPositionX(posX);
            widget->SetPositionY(GetPositionY() + margin);
            widget->UpdateBounds();
            widget->Update();
            posX += widget->GetWidth() + padding;
        }
    }
};
