// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Core/RApplication.hpp"

void RApplication::Update()
{
    if (rui::GetWindowSize() != lastWindowSize)
    {
        lastWindowSize = rui::GetWindowSize();
        updateBounds = true;
    }
    if (updateBounds)
    {
        updateBounds = false;
        for (auto& window: windows)
        {
            if (window->IsVisible()) window->UpdateBounds();
        }
    }
    for (auto& window: windows)
    {
        if (window->IsVisible()) window->Update();
    }
}

void RApplication::Draw()
{
    for (auto& window: windows)
    {
        if (window->IsVisible()) window->Draw();
    }
}
