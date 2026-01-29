// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RWindow
 */

#pragma once

#include "RCore/RContainer.hpp"
#include <functional>
#include <memory>

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

/**
 * @brief An event for RWindow
 * @p func is called if @p event () returns true
 * The event is deleted if any of @p dependencies becomes null
 */
struct REvent
{
    std::vector<std::weak_ptr<void>> dependencies;
    std::function<bool()> event;
    std::function<void()> func;

    bool IsValid() const
    {
        if (!event || !func) return false;
        for (auto& dep: dependencies)
        {
            if (dep.expired()) return false;
        }
        return true;
    }
};

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

/**
 * @brief A window that takes the whole render space
 */
class RWindow : public RContainer
{
  public:
    virtual ~RWindow() = default;

    void Update() override;

    void SetScale(float scale) override;

    template <typename... Tracker>
    void Connect(std::function<bool()> event, std::function<void()> func,
                 std::shared_ptr<Tracker>... deps)
    {
        REvent e;
        e.event = event;
        e.func = func;
        (e.dependencies.push_back(deps), ...);
        events.push_back(std::move(e));
    }

  protected:
    std::vector<REvent> events;

    void UpdateEvents();
};
