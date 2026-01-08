// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Windows/RPopupWindow.hpp"
#include "Api.hpp"

void RPopupWindow::ResetEvents()
{
    RWindow::ResetEvents();
    closeButton.ResetEvents();
}

bool RPopupWindow::PollEvents()
{
    if (PollCentralWidgetEvents()) return true;
    if (closeButton.PollEvents()) return true;
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

        closeButton.SetPosition({bounds.x + bounds.width - titleBarHeight, bounds.y});
        closeButton.UpdateBounds();

        if (centralWidget && centralWidget->IsVisible())
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

    for (auto& [event, func]: events)
    {
        if (event()) func();
    }

    closeButton.Update();
}

void RPopupWindow::Draw()
{
    float roundness = radius * 2 / std::min(bounds.width, bounds.height);
    rui::DrawRectangleRoundedBorder(bounds, roundness, segments, borderThickness, color, *theme,
                                    themeState);

    RRectangle titleBarBounds = bounds;
    titleBarBounds.height = titleBarHeight;
    float titleBarRoundness = radius * 2 / std::min(titleBarBounds.width, titleBarBounds.height);
    rui::DrawRectangleRoundedBorder(titleBarBounds, titleBarRoundness, segments, borderThickness,
                                    GetThemeColor(RThemeList::Secondary, themeState), *theme,
                                    themeState);

    closeButton.Draw();

    DrawCentralWidget();
}
