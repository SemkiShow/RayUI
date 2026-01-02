// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"
#include "Widgets/Containers/Layouts/RLayout.hpp"
#include <memory>

class RPane : public RWidget
{
  public:
    RPane(RColor color = {127, 127, 127, 127}) : color(color) {}
    virtual ~RPane() = default;

    void Update() override;
    void Draw() override;

    void SetColor(RColor col) { color = col; }

    RColor GetColor() { return color; }

    void SetLayout(std::shared_ptr<RLayout> val) { layout = val; }

  protected:
    RColor color;
    std::shared_ptr<RLayout> layout;
};
