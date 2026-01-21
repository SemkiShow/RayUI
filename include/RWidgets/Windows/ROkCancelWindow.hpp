// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RWidgets/Buttons/RLabelButton.hpp"
#include "RWidgets/Labels/RLabel.hpp"
#include "RWidgets/Layouts/RHBoxLayout.hpp"
#include "RWidgets/Layouts/RVBoxLayout.hpp"
#include "RWidgets/Windows/RPopupWindow.hpp"

class ROkCancelWindow : public RPopupWindow
{
  public:
    ROkCancelWindow(const std::string& message, const std::string& okText = "Ok",
                    const std::string& cancelText = "Cancel")
    {
        layout = std::make_shared<RVBoxLayout>();
        layout->SetMargin(0);
        SetCentralWidget(layout);

        messageLabel = std::make_shared<RLabel>(message);
        messageLabel->SetAlignment(RAlign::HCenter);
        layout->AddWidget(messageLabel);

        buttonLayout = std::make_shared<RHBoxLayout>();
        buttonLayout->SetMargin(0);
        buttonLayout->SetAlignment(RAlign::HCenter);
        buttonLayout->SetAlignment(RAlign::Bottom);
        layout->AddWidget(buttonLayout);

        okButton = std::make_shared<RLabelButton>(okText);
        buttonLayout->AddWidget(okButton);
        Connect([this]() { return IsOkClicked(); }, [this]() { SetVisible(false); }, okButton);

        cancelButton = std::make_shared<RLabelButton>(cancelText);
        buttonLayout->AddWidget(cancelButton);
        Connect([this]() { return IsCancelClicked(); }, [this]() { SetVisible(false); },
                cancelButton);

        layout->UpdateBounds();
        layout->Update();
        SetMaxWidth(std::max(GetMaxWidth(), layout->GetWidth() + 2 * margin));
        SetMaxHeight(std::max(GetMaxHeight(), layout->GetHeight() + 2 * margin + titleBarHeight));
    }
    virtual ~ROkCancelWindow() = default;

    void SetMessageText(const std::string& val)
    {
        messageLabel->SetLabel(val);
        UpdateBounds();
    }

    std::string GetMessageText() { return messageLabel->GetLabel(); }

    std::string GetMessageTextId() { return messageLabel->GetLabelId(); }

    void SetOkText(const std::string& val)
    {
        okButton->SetLabel(val);
        UpdateBounds();
    }

    std::string GetOkText() { return okButton->GetLabel(); }

    void SetCancelText(const std::string& val)
    {
        cancelButton->SetLabel(val);
        UpdateBounds();
    }

    std::string GetCancelText() { return cancelButton->GetLabel(); }

    bool IsOkClicked() { return okButton->IsClicked(); }
    bool IsCancelClicked() { return cancelButton->IsClicked(); }

  private:
    std::shared_ptr<RVBoxLayout> layout;
    std::shared_ptr<RHBoxLayout> buttonLayout;
    std::shared_ptr<RLabel> messageLabel;
    std::shared_ptr<RLabelButton> okButton, cancelButton;
};
