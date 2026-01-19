// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/Layouts/RLayout.hpp"

void RLayout::ResetEvents()
{
    for (auto& widget: widgets)
        widget->ResetEvents();
    RWidget::ResetEvents();
}

bool RLayout::PollEvents()
{
    if (PollWidgetsEvents()) return true;
    return RWidget::PollEvents();
}

void RLayout::Update()
{
    if (updateBounds)
    {
        updateBounds = false;
        bounds = ClampBounds(bounds, minSize, maxSize);
        for (auto& widget: widgets)
        {
            widget->UpdateBounds();
        }
    }
    UpdateWidgets();
}

void RLayout::Draw()
{
    for (auto& widget: widgets)
    {
        if (widget->IsVisible()) widget->Draw();
    }
}

void RLayout::UpdateLabels()
{
    for (auto& widget: widgets)
    {
        widget->UpdateLabels();
    }
    RWidget::UpdateLabels();
    UpdateBounds();
}

void RLayout::DrawDebugOutline()
{
    RWidget::DrawDebugOutline();
    for (auto& widget: widgets)
    {
        if (!widget->IsVisible()) continue;

        widget->DrawDebugOutline();
    }
}

void RLayout::SetFont(std::shared_ptr<RFont> font)
{
    for (auto& widget: widgets)
    {
        widget->SetFont(font);
    }
    RWidget::SetFont(font);
}

void RLayout::SetTheme(std::shared_ptr<RTheme> theme)
{
    for (auto& widget: widgets)
    {
        widget->SetTheme(theme);
    }
    RWidget::SetTheme(theme);
}

void RLayout::SetScale(float scale)
{
    for (auto& widget: widgets)
    {
        widget->SetScale(scale);
    }
    float delta = scale / this->scale;
    margin *= delta;
    padding *= delta;
    RWidget::SetScale(scale);
}
