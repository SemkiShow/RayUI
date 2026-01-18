// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "RCore/Utils.hpp"
#include <filesystem>
#include <string>
#include <vector>

enum class IconType
{
    Info,
    Warning,
    Error
};

enum class DialogType
{
    Ok,
    OkCancel,
    YesNo,
    YesNoCancel
};

enum class DialogButton
{
    Ok,
    Cancel,
    Yes,
    No
};

void ShowPopupNotification(const std::string& title, const std::string& message, IconType iconType);

DialogButton ShowMessageBox(const std::string& title, const std::string& message,
                            DialogType dialogType, IconType iconType, DialogButton defaultButton);

std::string ShowInputBox(const std::string& title, const std::string& message,
                         const std::string& defaultInput, bool isPassword = false);

std::string ShowSaveFileDialog(const std::string& title, const std::filesystem::path& defaultPath,
                               const std::vector<std::string>& filterPatterns,
                               const std::string& filterDescription);

std::vector<std::string> ShowOpenFileDialog(const std::string& title,
                                            const std::filesystem::path& defaultPath,
                                            const std::vector<std::string>& filterPatterns,
                                            const std::string& filterDescription,
                                            bool allowMultipleSelects);

std::string ShowSelectFolderDialog(const std::string& title,
                                   const std::filesystem::path& defaultPath);

RColor ShowColorPicker(const std::string& title, const std::string& defaultRbgHex);
RColor ShowColorPicker(const std::string& title, const unsigned char defaultRgb[3]);
std::string ShowColorPickerHex(const std::string& title, const std::string& defaultRbgHex);
std::string ShowColorPickerHex(const std::string& title, const unsigned char defaultRgb[3]);

void OpenLink(const std::string& url);
