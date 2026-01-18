// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Panes/RPane.hpp"

void RPane::ResetEvents()
{
    if (centralWidget) centralWidget->ResetEvents();
    RWidget::ResetEvents();
}

bool RPane::PollEvents()
{
    if (PollCentralWidgetEvents()) return true;
    return RWidget::PollEvents();
}

void RPane::Update()
{
    RWidget::UpdateColors();

    if (updateBounds)
    {
        updateBounds = false;
        bounds = ClampBounds(bounds, minSize, maxSize);
        if (centralWidget && centralWidget->IsVisible())
        {
            centralWidget->SetBounds(GetBounds());
            centralWidget->UpdateBounds();
        }
    }
    if (centralWidget && centralWidget->IsVisible()) centralWidget->Update();
}

void RPane::UpdateLabels()
{
    if (centralWidget) centralWidget->UpdateLabels();
    RWidget::UpdateLabels();
    UpdateBounds();
}

void RPane::DrawDebugOutline()
{
    RWidget::DrawDebugOutline();
    if (centralWidget && centralWidget->IsVisible()) centralWidget->DrawDebugOutline();
}

void RPane::Draw()
{
    rui::DrawRectangleBorder(bounds, drawBorder, borderThickness, color, *theme, themeState);
    DrawCentralWidget();
}

void RPane::SetFont(std::shared_ptr<RFont> font)
{
    if (centralWidget) centralWidget->SetFont(font);
    RWidget::SetFont(font);
}

void RPane::SetTheme(std::shared_ptr<RTheme> theme)
{
    if (centralWidget) centralWidget->SetTheme(theme);
    RWidget::SetTheme(theme);
}

void RPane::SetScale(float scale)
{
    if (centralWidget) centralWidget->SetScale(scale);
    RWidget::SetScale(scale);
}
