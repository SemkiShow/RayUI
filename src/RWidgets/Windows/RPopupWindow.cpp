// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Windows/RPopupWindow.hpp"
#include "RCore/Api.hpp"
#include <algorithm>

void RPopupWindow::ResetEvents()
{
    closeButton->ResetEvents();
    RWindow::ResetEvents();
}

bool RPopupWindow::PollEvents()
{
    if (closeButton->PollEvents()) return true;
    if (PollCentralWidgetEvents()) return true;
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
            selected = true;
        }
    }
    if (rui::IsMouseButtonReleased(RMouseButton::Left))
    {
        selected = false;
    }

    if (selected)
    {
        bounds.SetPosition(bounds.GetPosition() + rui::GetMouseDelta());
        UpdateBounds();
    }

    if (updateBounds)
    {
        bounds = ClampBounds(bounds, minSize, maxSize);

        auto windowSize = rui::GetWindowSize();
        float outOfWindowMargin = 2 * titleBarHeight;
        bounds.x = std::clamp(bounds.x, outOfWindowMargin - bounds.width,
                              windowSize.x - outOfWindowMargin);
        bounds.y = std::clamp(bounds.y, outOfWindowMargin - bounds.height,
                              windowSize.y - outOfWindowMargin);

        closeButton->SetPosition({bounds.x + bounds.width - titleBarHeight, bounds.y});
        closeButton->UpdateBounds();
    }
    closeButton->Update();

    RWindow::Update();
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

void RPopupWindow::SetCentralWidgetsBounds()
{
    if (centralWidget)
    {
        auto centralWidgetBounds = AddMargin(bounds, margin);
        centralWidgetBounds.y += titleBarHeight;
        centralWidgetBounds.height -= titleBarHeight;
        centralWidget->SetBounds(centralWidgetBounds);
        centralWidget->UpdateBounds();
    }
}
