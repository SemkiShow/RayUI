// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RImage
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RCore/RWidget.hpp"

/**
 * @brief A widget with a texture
 */
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
