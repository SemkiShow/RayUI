// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/RWidget.hpp"

class RImage : public RWidget
{
  public:
    RImage(RTexture texture) : texture(texture) {}
    virtual ~RImage() = default;

    void Shrink() override;
    void Draw() override;

    void SetTexture(RTexture val) { texture = val; }

    RTexture GetTexture() { return texture; }

  protected:
    RTexture texture;
};
