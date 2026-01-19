// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/Icons.hpp"
#include "RCore/Api.hpp"
#include "raygui_icons.h"

namespace rui
{

void DrawIcon(RIcon icon, RVector2 pos, float size, RColor color)
{
    const float pixelSize = size / RAYGUI_ICON_SIZE;
    const int iconIdx = static_cast<int>(icon) * RAYGUI_ICON_DATA_ELEMENTS;
    const int totalBits = RAYGUI_ICON_SIZE * RAYGUI_ICON_SIZE;

    float y = 0;
    for (int i = 0; i < totalBits / 32; i++)
    {
        for (int k = 0; k < 32; k++)
        {
            if (guiIcons[iconIdx + i] & (1u << k))
            {
                float x = (k % RAYGUI_ICON_SIZE) * pixelSize;

                rui::DrawRectangle({pos.x + x, pos.y + y * pixelSize, pixelSize, pixelSize}, color);
            }

            if (k == 15 || k == 31) y++;
        }
    }
}

} // namespace rui
