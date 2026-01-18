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

    for (int bitIndex = 0; bitIndex < totalBits; bitIndex++)
    {
        int idx = bitIndex / 32;
        int bitShift = bitIndex % 32;

        if (guiIcons[iconIdx + idx] & (1u << bitShift))
        {
            float x = (bitIndex % RAYGUI_ICON_SIZE) * pixelSize;
            float y = (bitIndex * 1.0f / RAYGUI_ICON_SIZE) * pixelSize;

            rui::DrawRectangle({pos.x + x, pos.y + y, pixelSize, pixelSize}, color);
        }
    }
}

} // namespace rui
