// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Windows/RPopupWindow.hpp"
#include "RCore/Api.hpp"
#include <algorithm>

void RPopupWindow::ResetEvents()
{
    RWindow::ResetEvents();
    closeButton->ResetEvents();
}

bool RPopupWindow::PollEvents()
{
    if (PollCentralWidgetEvents()) return true;
    if (closeButton->PollEvents()) return true;
    return RWidget::PollEvents();
}

void RPopupWindow::Update()
{
    if (IsMouseLeftPressed())
    {
        RRectangle titleBarBounds = bounds;
        titleBarBounds.width -= titleBarHeight;
        titleBarBounds.height = titleBarHeight;
        if (titleBarBounds.IsInside(rui::GetMousePosition()))
        {
            lastMousePosition = rui::GetMousePosition();
            selected = true;
        }
    }
    if (rui::IsMouseButtonReleased(RMouseButton::Left))
    {
        selected = false;
    }

    if (selected)
    {
        RVector2 delta = rui::GetMousePosition() - lastMousePosition;
        bounds.SetPosition(bounds.GetPosition() + delta);
        UpdateBounds();
        lastMousePosition = rui::GetMousePosition();
    }

    if (updateBounds)
    {
        updateBounds = false;

        auto windowSize = rui::GetWindowSize();
        SetSize(GetMaxSize());
        if (maxSize.x < 0) SetWidth(windowSize.x);
        if (maxSize.y < 0) SetHeight(windowSize.y);
        bounds = ClampBounds(bounds, minSize, maxSize);

        float outOfWindowMargin = 2 * titleBarHeight;
        bounds.x = std::clamp(bounds.x, outOfWindowMargin - bounds.width,
                              windowSize.x - outOfWindowMargin);
        bounds.y = std::clamp(bounds.y, outOfWindowMargin - bounds.height,
                              windowSize.y - outOfWindowMargin);

        closeButton->SetPosition({bounds.x + bounds.width - titleBarHeight, bounds.y});
        closeButton->UpdateBounds();

        if (centralWidget)
        {
            auto centralWidgetBounds = GetBounds();
            centralWidgetBounds.y += titleBarHeight;
            centralWidgetBounds.height -= titleBarHeight;

            centralWidgetBounds = AddMargin(centralWidgetBounds, margin);
            centralWidget->SetBounds(centralWidgetBounds);
            centralWidget->UpdateBounds();
        }
    }
    if (centralWidget && centralWidget->IsVisible()) centralWidget->Update();
    closeButton->Update();

    for (auto it = events.begin(); it != events.end();)
    {
        if (it->tracker.expired())
        {
            it = events.erase(it);
            continue;
        }

        if (it->event())
        {
            it->func();
        }
        ++it;
    }
}

void RPopupWindow::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, drawBorder, borderThickness, color,
                                    *theme, themeState);

    RRectangle titleBarBounds = bounds;
    titleBarBounds.height = titleBarHeight;
    float titleBarRoundness = radius * 2 / std::min(titleBarBounds.width, titleBarBounds.height);
    rui::DrawRectangleRoundedBorder(
        titleBarBounds, titleBarRoundness, segments, drawBorder, borderThickness,
        GetThemeColor(RThemeList::Secondary, themeState), *theme, themeState);

    closeButton->Draw();

    DrawCentralWidget();
}
