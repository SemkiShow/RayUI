// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Panes/RPane.hpp"

void RPane::ResetEvents()
{
    if (layout) layout->ResetEvents();
    RWidget::ResetEvents();
}

bool RPane::PollEvents()
{
    if (PollLayoutEvents()) return true;
    return RWidget::PollEvents();
}

void RPane::Update()
{
    RWidget::UpdateColors();

    if (updateBounds)
    {
        updateBounds = false;
        bounds = ClampBounds(bounds, minSize, maxSize);
        if (layout && layout->IsVisible())
        {
            layout->SetBounds(GetBounds());
            layout->UpdateBounds();
        }
    }
    if (layout && layout->IsVisible()) layout->Update();
}

void RPane::UpdateLabels()
{
    if (layout) layout->UpdateLabels();
    RWidget::UpdateLabels();
}

void RPane::Draw()
{
    rui::DrawRectangleBorder(bounds, drawBorder, borderThickness, color, *theme, themeState);
    DrawLayout();
}

void RPane::SetFont(std::shared_ptr<RFont> font)
{
    if (layout) layout->SetFont(font);
    RWidget::SetFont(font);
}

void RPane::SetTheme(std::shared_ptr<RTheme> theme)
{
    if (layout) layout->SetTheme(theme);
    RWidget::SetTheme(theme);
}

void RPane::SetScale(float scale)
{
    if (layout) layout->SetScale(scale);
    RWidget::SetScale(scale);
}
