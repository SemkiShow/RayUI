// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/RApplication.hpp"
#include "Api.hpp"

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

    for (auto& window: windows)
    {
        window->ResetEvents();
    }
    PollEvents();

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

void RApplication::SetFont(std::shared_ptr<RFont> font)
{
    for (auto& window: windows)
    {
        window->SetFont(font);
    }
}

void RApplication::SetTheme(std::shared_ptr<RTheme> theme)
{
    for (auto& window: windows)
    {
        window->SetTheme(theme);
    }
}

void RApplication::SetScale(float val)
{
    for (auto& window: windows)
    {
        window->SetScale(val);
    }
}
