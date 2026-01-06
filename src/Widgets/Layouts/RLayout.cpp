// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Layouts/RLayout.hpp"

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
        for (auto& widget: widgets)
        {
            if (widget->IsVisible()) widget->UpdateBounds();
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
