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
 * @defgroup Widgets
 * @{
 * @defgroup Windows
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
 * @brief A window that takes the whole render space
 */
class RWindow : public RContainer
{
  public:
    virtual ~RWindow() = default;

    void Update() override;

    void SetScale(float scale) override;

    /**
     * @brief A function for attaching events to RWindow
     * @warning Use this function carefully. If @p event and/or @p func is a lambda capturing a
     * widget, then make sure that this widget is destroyed only once the window destructor is
     * called, not before that. If this requirement is met, then your code can look like this:
     * @code {.cpp}
     * auto button = std::make_shared<RButton>();
     *
     * Connect([button] { return button->IsClicked(); }, [] { std::cout << "Button was
     * clicked!\n"; });
     * @endcode
     * If you want to attach an event to a widget that can be destroyed, use a weak pointer to
     * prevent the lambda from keeping the widget from being destroyed and make the original
     * std::shared_ptr a dependency of the connection. This will destroy the connection once the
     * widget is destroyed
     * @code {.cpp}
     * auto button = std::make_shared<RButton>();
     *
     * std::weak_ptr<RButton> weakButton = button;
     * Connect(
     *     [weakButton]
     *     {
     *         if (auto btn = weakButton.lock()) return btn->IsClicked();
     *         return false;
     *     },
     *     []{ std::cout << "Button was clicked!\n"; }, button);
     * @endcode
     * @tparam Tracker
     * @param event
     * @param func
     * @param deps
     */
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
