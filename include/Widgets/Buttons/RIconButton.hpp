// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/Icons.hpp"
#include "Widgets/Buttons/RButton.hpp"

class RIconButton : public RButton
{
  public:
    RIconButton(RIcon icon) : icon(icon)
    {
        maxSize.x = minSize.x;
        maxSize.y = minSize.y;
    }
    virtual ~RIconButton() = default;

    void Draw() override;

  protected:
    RIcon icon;
};
