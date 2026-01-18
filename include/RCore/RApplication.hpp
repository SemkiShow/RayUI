// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RWidgets/Windows/RWindow.hpp"
#include <filesystem>
#include <memory>
#include <vector>

class RApplication
{
  public:
    virtual ~RApplication() = default;

    virtual void ResetEvents();
    virtual bool PollEvents();
    virtual void Update();
    virtual void Draw();

    virtual void SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                             const std::string& language);
    virtual void UpdateLabels();

    void UpdateBounds() { updateBounds = true; }

    void AddWindow(std::shared_ptr<RWindow> window) { windows.push_back(window); }

    void InsertWindow(size_t idx, std::shared_ptr<RWindow> window)
    {
        if (idx > windows.size()) throw std::runtime_error("Invalid idx in InsertWindow!");
        windows.insert(windows.begin() + idx, window);
    }

    void EraseWindow(size_t idx)
    {
        if (idx >= windows.size()) throw std::runtime_error("Invalid idx in EraseWindow!");
        windows.erase(windows.begin() + idx);
    }

    void PopBack()
    {
        if (windows.empty())
            throw std::runtime_error("PopBack is called on an empty RApplication!");
        windows.pop_back();
    }

    void ClearWindows() { windows.clear(); }

    std::shared_ptr<RWindow> GetWindow(size_t idx)
    {
        if (idx >= windows.size()) throw std::runtime_error("Invalid idx in GetWindow!");
        return windows[idx];
    }

    void SetFont(std::shared_ptr<RFont> font);

    void SetTheme(std::shared_ptr<RTheme> theme);

    void SetScale(float val);

    void SetDebugMode(bool val)
    {
        for (auto& window: windows)
            window->SetDebugMode(val);
        debugMode = val;
    }

    bool IsDebugMode() { return debugMode; }

    virtual void DrawDebugOutline();

    bool IsWindowSizeChanged() { return windowSizeChanged; }

  protected:
    bool updateBounds = true;
    std::vector<std::shared_ptr<RWindow>> windows;
    bool debugMode = false;

  private:
    RVector2 lastWindowSize{-1, -1};
    bool windowSizeChanged = false;
};
