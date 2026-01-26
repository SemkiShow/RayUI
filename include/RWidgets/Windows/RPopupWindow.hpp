// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/Api.hpp"
#include "RWidgets/Buttons/RIconButton.hpp"
#include "RWidgets/Windows/RWindow.hpp"

class RPopupWindow : public RWindow
{
  public:
    RPopupWindow(float titleBarHeight = 20, float radius = 5, int segments = 5)
        : titleBarHeight(titleBarHeight), radius(radius), segments(segments)
    {
        maxSize.x = 16 * minSize.x;
        maxSize.y = 9 * minSize.y;
        bounds.SetPosition((rui::GetWindowSize() - maxSize) / 2);
        SetAnimated(false);

        closeButton = std::make_shared<RIconButton>(RIcon::Cross);
        closeButton->SetMaxSize({titleBarHeight, titleBarHeight});

        Connect([this]() { return closeButton->IsClicked(); }, [this]() { SetVisible(false); },
                closeButton);
    }
    virtual ~RPopupWindow() = default;

    void ResetEvents() override;
    bool PollEvents() override;
    void Update() override;
    void Draw() override;

    void SetTitleBarHeight(float val) { titleBarHeight = val; }

    float GetTitleBarHeight() { return titleBarHeight; }

    void SetRadius(float val) { radius = val; }

    float GetRadius() { return radius; }

    void SetSegments(int val) { segments = val; }

    int GetSegments() { return segments; }

    void SetDraggable(bool val) { draggable = val; }

    bool IsDraggable() { return draggable; }

    bool IsSelected() { return selected; }

  protected:
    float titleBarHeight = 20;
    float radius = 5;
    int segments = 5;
    bool selected = false, draggable = true;

    void SetCentralWidgetsBounds() override;

  private:
    std::shared_ptr<RIconButton> closeButton;
};
