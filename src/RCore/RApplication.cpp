// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/RApplication.hpp"
#include "RCore/Api.hpp"
#include "RCore/Translations.hpp"

void RApplication::ResetEvents()
{
    for (auto& window: windows)
    {
        window->ResetEvents();
    }
}

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
    if (windowSizeChanged) windowSizeChanged = false;
    if (rui::GetWindowSize() != lastWindowSize)
    {
        lastWindowSize = rui::GetWindowSize();
        updateBounds = true;
        windowSizeChanged = true;
    }
    if (updateBounds)
    {
        updateBounds = false;
        for (auto& window: windows)
        {
            window->UpdateBounds();
        }
    }

    ResetEvents();
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
        if (!window->IsVisible()) continue;

        window->Draw();
        if (debugMode) window->DrawDebugOutline();
    }
}

void RApplication::UpdateLabels()
{
    for (auto& window: windows)
    {
        window->UpdateLabels();
    }
    UpdateBounds();
}

void RApplication::SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                               const std::string& language)
{
    ::SetLanguage(domain, localePath, language);
    UpdateLabels();
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

void RApplication::DrawDebugOutline()
{
    for (auto& window: windows)
    {
        if (!window->IsVisible()) continue;

        window->DrawDebugOutline();
    }
}
