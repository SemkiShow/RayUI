// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Widgets/Panes/RPane.hpp"
#include "Api.hpp"

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
    if (customColor) color = tint;

    if (updateBounds)
    {
        updateBounds = false;
        if (layout && layout->IsVisible())
        {
            layout->SetBounds(GetBounds());
            layout->UpdateBounds();
        }
    }
    if (layout && layout->IsVisible()) layout->Update();
}

void RPane::Draw()
{
    rui::DrawRectangle(bounds, color);
    rui::DrawRectangleLines(bounds, borderThickness, GetThemeColor(RThemeList::Border, themeState));
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
