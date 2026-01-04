// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Api.hpp"
#include "Core/RApplication.hpp"

bool RApplication::PollEvents()
{
    for (int i = windows.size() - 1; i >= 0; i--)
    {
        if (windows[i]->IsVisible() && windows[i]->PollEvents()) return true;
    }
    return false;
}

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

    PollEvents();

    for (auto& window: windows)
    {
        if (window->IsVisible()) window->Update();
        window->ResetEvents();
    }
}

void RApplication::Draw()
{
    for (auto& window: windows)
    {
        if (window->IsVisible()) window->Draw();
    }
}
