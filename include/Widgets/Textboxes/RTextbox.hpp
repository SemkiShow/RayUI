// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/RWidget.hpp"

class RTextbox : public RWidget
{
  public:
    RTextbox(const std::string& promptText = "", const std::string& text = "")
        : promptText(promptText), text(text)
    {
        maxSize.y = minSize.y;
    }
    virtual ~RTextbox() = default;

    void Update() override;
    void Draw() override;

    void SetScale(float val) override
    {
        float delta = val / scale;
        margin *= delta;
        RWidget::SetScale(val);
    }

    void SetPromptText(const std::string& val) { promptText = val; }

    std::string GetPromptText() { return promptText; }

    void SetText(const std::string& val) { text = val; }

    std::string GetText() { return text; }

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
    std::string promptText, text;
    bool selected = false;
    float radius = 3;
    int segments = 16;
    float margin = 5;
    bool finishedEditing = false;
};
