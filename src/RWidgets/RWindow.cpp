// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RWidgets/RWindow.hpp"

void RWindow::Update()
{
    RContainer::Update();

    UpdateEvents();
}

void RWindow::SetScale(float scale)
{
    float delta = scale / this->scale;
    margin *= delta;
    RContainer::SetScale(scale);
}

void RWindow::UpdateEvents()
{
    std::vector<std::function<void()>> actionsToRun;

    for (auto it = events.begin(); it != events.end();)
    {
        if (!it->IsValid())
        {
            it = events.erase(it);
            continue;
        }

        if (it->event && it->event())
        {
            actionsToRun.push_back(it->func);
        }
        ++it;
    }

    for (const auto& action: actionsToRun)
    {
        action();
    }
}
