// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/ScrollAreas/RScrollArea.hpp"
#include "RCore/Api.hpp"
#include <algorithm>

void RScrollArea::ResetEvents()
{
    vBar.ResetEvents();
    hBar.ResetEvents();
    RContainer::ResetEvents();
}

bool RScrollArea::PollEvents()
{
    if (vBar.IsVisible() && vBar.PollEvents()) return true;
    if (hBar.IsVisible() && hBar.PollEvents()) return true;
    return RContainer::PollEvents();
}

void RScrollArea::Update()
{
    bool wasUpdateBounds = updateBounds;
    RContainer::Update();

    vBar.SetVisible(enabled && centralWidget->GetHeight() > GetHeight());
    hBar.SetVisible(enabled && centralWidget->GetWidth() > GetWidth());

    auto mouseDelta = rui::GetMouseDelta();

    if (vBar.IsMouseLeftPressed()) vBarActive = true;
    if (hBar.IsMouseLeftPressed()) hBarActive = true;
    if (rui::IsMouseButtonReleased(RMouseButton::Left))
    {
        vBarActive = false;
        hBarActive = false;
    }

    if (wasUpdateBounds)
    {
        centralWidgetDrawBounds = bounds;
        if (vBar.IsVisible()) centralWidgetDrawBounds.width -= barSize;
        if (hBar.IsVisible()) centralWidgetDrawBounds.height -= barSize;

        auto vBarBounds = bounds;
        vBarBounds.width = barSize;
        if (hBar.IsVisible()) vBarBounds.height -= barSize;
        vBarBounds.height *= vBarBounds.height / centralWidget->GetHeight();
        vBarBounds.x = bounds.x + bounds.width - vBarBounds.width;
        vBarBounds.y = std::max(bounds.y, vBar.GetPositionY());
        vBar.SetBounds(vBarBounds);
        vBar.UpdateBounds();

        auto hBarBounds = bounds;
        hBarBounds.height = barSize;
        if (vBar.IsVisible()) hBarBounds.width -= barSize;
        hBarBounds.width *= hBarBounds.width / centralWidget->GetWidth();
        hBarBounds.x = std::max(bounds.x, hBar.GetPositionX());
        hBarBounds.y = bounds.y + bounds.height - hBarBounds.height;
        hBar.SetBounds(hBarBounds);
        hBar.UpdateBounds();
    }

    if (bounds.IsInside(rui::GetMousePosition()) && vBar.IsVisible())
    {
        auto wheelMove = rui::GetMouseWheelMove().y * wheelSensitivity * scale;
        vBar.SetPositionY(vBar.GetPositionY() - wheelMove);
        if (wheelMove != 0) UpdateBounds();
    }
    if (vBarActive)
    {
        vBar.SetPositionY(vBar.GetPositionY() + mouseDelta.y);
        if (mouseDelta.y != 0) UpdateBounds();
    }
    vBar.SetPositionY(
        std::clamp(vBar.GetPositionY(), bounds.y, bounds.y + bounds.height - vBar.GetHeight()));

    if (bounds.IsInside(rui::GetMousePosition()) && hBar.IsVisible())
    {
        auto wheelMove = rui::GetMouseWheelMove().x * wheelSensitivity * scale;
        hBar.SetPositionX(hBar.GetPositionX() - wheelMove);
        if (wheelMove != 0) UpdateBounds();
    }
    if (hBarActive)
    {
        hBar.SetPositionX(hBar.GetPositionX() + mouseDelta.x);
        if (mouseDelta.x != 0) UpdateBounds();
    }
    hBar.SetPositionX(
        std::clamp(hBar.GetPositionX(), bounds.x, bounds.x + bounds.width - hBar.GetWidth()));

    if (vBar.IsVisible()) vBar.Update();
    if (hBar.IsVisible()) hBar.Update();
}

void RScrollArea::Draw()
{
    rui::BeginScissorMode(centralWidgetDrawBounds);
    DrawCentralWidget();
    rui::EndScissorMode();

    if (vBar.IsVisible())
    {
        auto borderBounds = vBar.GetBounds();
        borderBounds.y = bounds.y;
        borderBounds.height = bounds.height;
        if (hBar.IsVisible()) borderBounds.height -= barSize;
        rui::DrawRectangleRounded(vBar.GetBounds(), barRadius, barSegments, vBar.GetThemeColor());
        rui::DrawRectangleRoundedLines(borderBounds, barRadius, barSegments, borderThickness,
                                       GetThemeColor(RThemeList::Border, vBar.GetThemeState()));
    }

    if (hBar.IsVisible())
    {
        auto borderBounds = hBar.GetBounds();
        borderBounds.x = bounds.x;
        borderBounds.width = bounds.width;
        if (vBar.IsVisible()) borderBounds.width -= barSize;
        rui::DrawRectangleRounded(hBar.GetBounds(), barRadius, barSegments, hBar.GetThemeColor());
        rui::DrawRectangleRoundedLines(borderBounds, barRadius, barSegments, borderThickness,
                                       GetThemeColor(RThemeList::Border, hBar.GetThemeState()));
    }
}

void RScrollArea::SetScale(float scale)
{
    float delta = scale / this->scale;
    barSize *= delta;
    RContainer::SetScale(scale);
    vBar.SetScale(scale);
    hBar.SetScale(scale);
}

void RScrollArea::SetCentralWidgetsBounds()
{
    if (centralWidget)
    {
        auto centralWidgetBounds = bounds;
        if (vBar.IsVisible()) centralWidgetBounds.width -= barSize;
        if (hBar.IsVisible()) centralWidgetBounds.height -= barSize;
        centralWidget->SetBounds(centralWidgetBounds);
        centralWidget->UpdateBounds();
        centralWidget->Update();

        centralWidgetBounds.x =
            Map(hBar.GetPositionX(), bounds.x, bounds.x + bounds.width - hBar.GetWidth(), bounds.x,
                bounds.x + bounds.width - centralWidget->GetWidth());
        centralWidgetBounds.y =
            Map(vBar.GetPositionY(), bounds.y, bounds.y + bounds.height - vBar.GetHeight(),
                bounds.y, bounds.y + bounds.height - centralWidget->GetHeight());
        centralWidget->SetBounds(centralWidgetBounds);
        centralWidget->UpdateBounds();
    }
}
