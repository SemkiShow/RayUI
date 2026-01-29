// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RImage.hpp"
#include "RCore/Api.hpp"

void RImage::Shrink()
{
    auto textureBounds = bounds;
    textureBounds.width =
        std::min(textureBounds.width, bounds.height * texture.width / texture.height);
    textureBounds.height =
        std::min(textureBounds.height, bounds.width * texture.height / texture.width);
    bounds = textureBounds;
}

void RImage::Draw() { rui::DrawTexture(texture, bounds, color); }
