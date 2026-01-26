// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/RContainer.hpp"

void RContainer::ResetEvents()
{
    if (centralWidget) centralWidget->ResetEvents();
    RWidget::ResetEvents();
}

bool RContainer::PollEvents()
{
    if (PollCentralWidgetEvents()) return true;
    return RWidget::PollEvents();
}

void RContainer::Update()
{
    if (centralWidget && centralWidget->IsDeleteLater()) UnsetCentralWidget();
    RWidget::UpdateColors();

    if (updateBounds)
    {
        updateBounds = false;
        bounds = ClampBounds(bounds, minSize, maxSize);

        SetCentralWidgetsBounds();
    }
    if (centralWidget && centralWidget->IsVisible()) centralWidget->Update();
}

void RContainer::Draw() { DrawCentralWidget(); }

void RContainer::UpdateLabels()
{
    if (centralWidget) centralWidget->UpdateLabels();
    RWidget::UpdateLabels();
    UpdateBounds();
}

void RContainer::SetDebugMode(bool val)
{
    if (centralWidget) centralWidget->SetDebugMode(val);
    debugMode = val;
}

void RContainer::DrawDebugOutline()
{
    RWidget::DrawDebugOutline();
    if (centralWidget && centralWidget->IsVisible()) centralWidget->DrawDebugOutline();
}

void RContainer::SetFont(std::shared_ptr<RFont> font)
{
    if (centralWidget) centralWidget->SetFont(font);
    RWidget::SetFont(font);
}

void RContainer::SetTheme(std::shared_ptr<RTheme> theme)
{
    if (centralWidget) centralWidget->SetTheme(theme);
    RWidget::SetTheme(theme);
}

void RContainer::SetScale(float scale)
{
    if (centralWidget) centralWidget->SetScale(scale);
    RWidget::SetScale(scale);
}
