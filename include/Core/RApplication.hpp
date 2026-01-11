// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Widgets/Windows/RWindow.hpp"
#include <filesystem>
#include <memory>
#include <vector>

class RApplication
{
  public:
    virtual ~RApplication() = default;

    virtual void Update();
    virtual void Draw();

    virtual void SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                             const std::string& language);
    virtual void UpdateLabels();

    void UpdateBounds() { updateBounds = true; }

    void AddWindow(std::shared_ptr<RWindow> window) { windows.push_back(window); }

    void SetFont(std::shared_ptr<RFont> font);

    void SetTheme(std::shared_ptr<RTheme> theme);

    void SetScale(float val);

    bool IsWindowSizeChanged() { return windowSizeChanged; }

  protected:
    bool updateBounds = true;
    std::vector<std::shared_ptr<RWindow>> windows;
    RVector2 lastWindowSize{-1, -1};

    virtual bool PollEvents();

  private:
    bool windowSizeChanged = false;
};
