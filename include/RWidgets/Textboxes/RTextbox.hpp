// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RTextbox
 */

#pragma once

/**
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#include "RCore/RWidget.hpp"

/**
 * @brief A textbox
 */
class RTextbox : public RWidget
{
  public:
    RTextbox(const std::string& promptText = "", const std::string& value = "")
        : promptTextId(promptText), value(value)
    {
        UpdateLabels();
        maxSize.y = minSize.y;
    }
    virtual ~RTextbox() = default;

    void Update() override;
    void Draw() override;

    void UpdateLabels() override;

    void SetScale(float val) override
    {
        float delta = val / scale;
        margin *= delta;
        RWidget::SetScale(val);
    }

    void SetPromptText(const std::string& val)
    {
        promptTextId = val;
        UpdateLabels();
    }

    std::string GetPromptText() { return promptText; }

    std::string GetPromptTextId() { return promptTextId; }

    void SetValue(const std::string& val) { value = val; }

    std::string GetValue() { return value; }

    void SetRadius(float val) { radius = val; }

    float GetRadius() { return radius; }

    void SetSegments(int val) { segments = val; }

    int GetSegments() { return segments; }

    void SetMargin(float val) { margin = val; }

    float GetMargin() { return margin; }

    void CheckEditing();

    bool IsSelected() { return selected; }
    bool IsFinishedEditing() { return finishedEditing; }

  protected:
    std::string promptText, promptTextId, value;
    bool selected = false;
    float radius = 5;
    int segments = 5;
    float margin = 5;
    bool finishedEditing = false;
};
