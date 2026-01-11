// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/Translations.hpp"
#include "Widgets/Buttons/RLabelButton.hpp"
#include "Widgets/Labels/RLabel.hpp"
#include "Widgets/Layouts/RHBoxLayout.hpp"
#include "Widgets/Layouts/RVBoxLayout.hpp"
#include "Widgets/Windows/RPopupWindow.hpp"

class ROkCancelWindow : public RPopupWindow
{
  public:
    ROkCancelWindow(const std::string& message, const std::string& okText = "Ok",
                    const std::string& cancelText = "Cancel")
    {
        maxSize.x = 8 * minSize.x;
        maxSize.y = 4 * minSize.y;

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
        okButton->SetAlignment(RAlign::HCenter);
        okButton->SetAlignment(RAlign::VCenter);
        buttonLayout->AddWidget(okButton);
        Connect([this]() { return IsOkClicked(); }, [this]() { SetVisible(false); });

        cancelButton = std::make_shared<RLabelButton>(cancelText);
        cancelButton->SetAlignment(RAlign::HCenter);
        cancelButton->SetAlignment(RAlign::VCenter);
        buttonLayout->AddWidget(cancelButton);
        Connect([this]() { return IsCancelClicked(); }, [this]() { SetVisible(false); });

        layout->UpdateBounds();
        layout->Update();
        SetMaxWidth(layout->GetWidth() + 2 * margin);
        SetMaxHeight(layout->GetHeight() + 2 * margin + titleBarHeight);
    }
    virtual ~ROkCancelWindow() = default;

    virtual void UpdateLabels() override
    {
        messageLabel->SetLabel(GetText(messageLabel->GetLabelId()));
        okButton->SetLabel(GetText(okButton->GetLabelId()));
        cancelButton->SetLabel(GetText(cancelButton->GetLabelId()));
        RWindow::UpdateLabels();
    }

    void SetMessageText(const std::string& val) { messageLabel->SetLabel(val); }

    std::string GetMessageText() { return messageLabel->GetLabel(); }

    std::string GetMessageTextId() { return messageLabel->GetLabelId(); }

    void SetOkText(const std::string& val) { okButton->SetLabel(val); }

    std::string GetOkText() { return okButton->GetLabel(); }

    void SetCancelText(const std::string& val) { cancelButton->SetLabel(val); }

    std::string GetCancelText() { return cancelButton->GetLabel(); }

    bool IsOkClicked() { return okButton->IsClicked(); }
    bool IsCancelClicked() { return cancelButton->IsClicked(); }

  private:
    std::shared_ptr<RVBoxLayout> layout;
    std::shared_ptr<RHBoxLayout> buttonLayout;
    std::shared_ptr<RLabel> messageLabel;
    std::shared_ptr<RLabelButton> okButton, cancelButton;
};
