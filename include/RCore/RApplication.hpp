// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RApplication
 */

#pragma once

#include "RWidgets/RWindow.hpp"
#include <filesystem>
#include <memory>
#include <vector>

/**
 * @defgroup Widgets
 * @{
 * @defgroup Application
 * @{
 */

/**
 * @brief The main object for storing windows
 */
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

    void AddWindow(std::shared_ptr<RWindow> window)
    {
        windows.push_back(window);
        UpdateBounds();
    }

    void InsertWindow(size_t idx, std::shared_ptr<RWindow> window)
    {
        if (idx > windows.size()) throw std::runtime_error("Invalid idx in InsertWindow!");
        windows.insert(windows.begin() + idx, window);
        UpdateBounds();
    }

    void EraseWindow(size_t idx)
    {
        if (idx >= windows.size()) throw std::runtime_error("Invalid idx in EraseWindow!");
        windows.erase(windows.begin() + idx);
        UpdateBounds();
    }

    void PopBack()
    {
        if (windows.empty())
            throw std::runtime_error("PopBack is called on an empty RApplication!");
        windows.pop_back();
        UpdateBounds();
    }

    void ClearWindows()
    {
        windows.clear();
        UpdateBounds();
    }

    std::shared_ptr<RWindow> GetWindow(size_t idx)
    {
        if (idx >= windows.size()) throw std::runtime_error("Invalid idx in GetWindow!");
        return windows[idx];
    }

    virtual void SetFont(std::shared_ptr<RFont> font);
    virtual void SetTheme(std::shared_ptr<RTheme> theme);
    virtual void SetScale(float val);
    virtual void SetDebugMode(bool val);
    virtual void DrawDebugOutline();

    bool IsDebugMode() { return debugMode; }

    bool IsWindowSizeChanged() { return windowSizeChanged; }

  protected:
    bool updateBounds = true;
    std::vector<std::shared_ptr<RWindow>> windows;
    bool debugMode = false;

  private:
    RVector2 lastWindowSize{-1, -1};
    bool windowSizeChanged = false;
};
