// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "Core/Native.hpp"
#include <tinyfiledialogs.h>

void ShowPopupNotification(const std::string& title, const std::string& message, IconType iconType)
{
    std::string iconTypeStr;
    switch (iconType)
    {
    case IconType::Info:
        iconTypeStr = "info";
        break;
    case IconType::Warning:
        iconTypeStr = "warning";
        break;
    case IconType::Error:
        iconTypeStr = "error";
        break;
    }

#ifdef _WIN32
    tinyfd_notifyPopupW(StringToWString(title).c_str(), StringToWString(message).c_str(),
                        StringToWString(iconTypeStr).c_str());
#else
    tinyfd_notifyPopup(title.c_str(), message.c_str(), iconTypeStr.c_str());
#endif
}

DialogButton ShowMessageBox(const std::string& title, const std::string& message,
                            DialogType dialogType, IconType iconType, DialogButton defaultButton)
{
    std::string iconTypeStr;
    switch (iconType)
    {
    case IconType::Info:
        iconTypeStr = "info";
        break;
    case IconType::Warning:
        iconTypeStr = "warning";
        break;
    case IconType::Error:
        iconTypeStr = "error";
        break;
    }

    std::string dialogTypeStr;
    switch (dialogType)
    {
    case DialogType::Ok:
        dialogTypeStr = "ok";
        break;
    case DialogType::OkCancel:
        dialogTypeStr = "okcancel";
        break;
    case DialogType::YesNo:
        dialogTypeStr = "yesno";
        break;
    case DialogType::YesNoCancel:
        dialogTypeStr = "yesnocancel";
        break;
    }

    int defaultButtonInt = 0;
    switch (defaultButton)
    {
    case DialogButton::Ok:
        defaultButtonInt = 1;
        break;
    case DialogButton::Cancel:
        defaultButtonInt = 0;
        break;
    case DialogButton::Yes:
        defaultButtonInt = 1;
        break;
    case DialogButton::No:
        if (dialogType == DialogType::YesNoCancel)
            defaultButtonInt = 2;
        else
            defaultButtonInt = 0;
        break;
    }

#ifdef _WIN32
    int result =
        tinyfd_messageBoxW(StringToWString(title).c_str(), StringToWString(message).c_str(),
                           StringToWString(dialogTypeStr).c_str(),
                           StringToWString(iconTypeStr).c_str(), defaultButtonInt);
#else
    int result = tinyfd_messageBox(title.c_str(), message.c_str(), dialogTypeStr.c_str(),
                                   iconTypeStr.c_str(), defaultButtonInt);
#endif

    switch (dialogType)
    {
    case DialogType::Ok:
        if (result)
            return DialogButton::Ok;
        else
            return DialogButton::Cancel;
        break;
    case DialogType::OkCancel:
        if (result)
            return DialogButton::Ok;
        else
            return DialogButton::Cancel;
        break;
    case DialogType::YesNo:
        if (result)
            return DialogButton::Yes;
        else
            return DialogButton::No;
        break;
    case DialogType::YesNoCancel:
        if (result == 1)
            return DialogButton::Yes;
        else if (result == 2)
            return DialogButton::No;
        else
            return DialogButton::Cancel;
        break;
    }
    return DialogButton::Cancel;
}

std::string ShowInputBox(const std::string& title, const std::string& message,
                         const std::string& defaultInput, bool isPassword)
{
#ifdef _WIN32
    auto res = tinyfd_inputBoxW(StringToWString(title).c_str(), StringToWString(message).c_str(),
                                (isPassword ? NULL : StringToWString(defaultInput).c_str()));
    if (!res) return "";
    return WStringToString(std::wstring(res));
#else
    auto res =
        tinyfd_inputBox(title.c_str(), message.c_str(), (isPassword ? NULL : defaultInput.c_str()));
    if (!res) return "";
    return res;
#endif
}

std::string ShowSaveFileDialog(const std::string& title, const std::filesystem::path& defaultPath,
                               const std::vector<std::string>& filterPatterns,
                               const std::string& filterDescription)
{
#ifdef _WIN32
    std::vector<const wchar_t*> filterPatternsChar;
    for (auto& pattern: filterPatterns)
    {
        filterPatternsChar.push_back(StringToWString(pattern).c_str());
    }
    auto res = tinyfd_saveFileDialogW(StringToWString(title).c_str(),
                                      StringToWString(defaultPath.string()).c_str(),
                                      filterPatternsChar.size(), filterPatternsChar.data(),
                                      StringToWString(filterDescription).c_str());
    if (!res) return "";
    return WStringToString(std::wstring(res));
#else
    std::vector<const char*> filterPatternsChar;
    for (auto& pattern: filterPatterns)
    {
        filterPatternsChar.push_back(pattern.c_str());
    }
    auto res = tinyfd_saveFileDialog(title.c_str(), defaultPath.c_str(), filterPatternsChar.size(),
                                     filterPatternsChar.data(), filterDescription.c_str());
    if (!res) return "";
    return res;
#endif
}

std::vector<std::string> ShowOpenFileDialog(const std::string& title,
                                            const std::filesystem::path& defaultPath,
                                            const std::vector<std::string>& filterPatterns,
                                            const std::string& filterDescription,
                                            bool allowMultipleSelects)
{
#ifdef _WIN32
    std::vector<const wchar_t*> filterPatternsChar;
    for (auto& pattern: filterPatterns)
    {
        filterPatternsChar.push_back(StringToWString(pattern).c_str());
    }
    auto res = tinyfd_openFileDialogW(
        StringToWString(title).c_str(), StringToWString(defaultPath.string()).c_str(),
        filterPatternsChar.size(), filterPatternsChar.data(),
        StringToWString(filterDescription).c_str(), allowMultipleSelects);
    if (!res) return {};
    return Split(WStringToString(std::wstring(res)), '|');
#else
    std::vector<const char*> filterPatternsChar;
    for (auto& pattern: filterPatterns)
    {
        filterPatternsChar.push_back(pattern.c_str());
    }
    auto res = tinyfd_openFileDialog(title.c_str(), defaultPath.c_str(), filterPatternsChar.size(),
                                     filterPatternsChar.data(), filterDescription.c_str(),
                                     allowMultipleSelects);
    if (!res) return {};
    return Split(res, '|');
#endif
}

std::string ShowSelectFolderDialog(const std::string& title,
                                   const std::filesystem::path& defaultPath)
{
#ifdef _WIN32
    auto res = tinyfd_selectFolderDialogW(StringToWString(title).c_str(),
                                          StringToWString(defaultPath.string()).c_str());
    if (!res) return "";
    return WStringToString(std::wstring(res));
#else
    auto res = tinyfd_selectFolderDialog(title.c_str(), defaultPath.c_str());
    if (!res) return "";
    return res;
#endif
}

RColor ShowColorPicker(const std::string& title, const std::string& defaultRbgHex)
{
#ifdef _WIN32
    unsigned char res[3]{0, 0, 0};
    tinyfd_colorChooserW(StringToWString(title).c_str(), StringToWString(defaultRbgHex).c_str(),
                         res, res);
    return {res[0], res[1], res[2]};
#else
    unsigned char res[3]{0, 0, 0};
    tinyfd_colorChooser(title.c_str(), defaultRbgHex.c_str(), res, res);
    return {res[0], res[1], res[2]};
#endif
}

RColor ShowColorPicker(const std::string& title, const unsigned char defaultRgb[3])
{
#ifdef _WIN32
    unsigned char res[3]{0, 0, 0};
    tinyfd_colorChooserW(StringToWString(title).c_str(), NULL, defaultRgb, res);
    return {res[0], res[1], res[2]};
#else
    unsigned char res[3]{0, 0, 0};
    tinyfd_colorChooser(title.c_str(), NULL, defaultRgb, res);
    return {res[0], res[1], res[2]};
#endif
}

std::string ShowColorPickerHex(const std::string& title, const std::string& defaultRbgHex)
{
#ifdef _WIN32
    unsigned char buf[3]{0, 0, 0};
    auto res = tinyfd_colorChooserW(StringToWString(title).c_str(),
                                    StringToWString(defaultRbgHex).c_str(), buf, buf);
    if (!res) return "";
    return WStringToString(std::wstring(res));
#else
    unsigned char buf[3]{0, 0, 0};
    auto res = tinyfd_colorChooser(title.c_str(), defaultRbgHex.c_str(), buf, buf);
    if (!res) return "";
    return res;
#endif
}

std::string ShowColorPickerHex(const std::string& title, const unsigned char defaultRgb[3])
{
#ifdef _WIN32
    unsigned char buf[3]{0, 0, 0};
    auto res = tinyfd_colorChooserW(StringToWString(title).c_str(), NULL, defaultRgb, buf);
    if (!res) return "";
    return WStringToString(std::wstring(res));
#else
    unsigned char buf[3]{0, 0, 0};
    auto res = tinyfd_colorChooser(title.c_str(), NULL, defaultRgb, buf);
    if (!res) return "";
    return res;
#endif
}

void OpenLink(const std::string& url)
{
#if defined(_WIN32) || defined(_WIN64)
    std::string command = "start " + url;
    std::system(command.c_str());

#elif defined(__APPLE__)
    std::string command = "open " + url;
    std::system(command.c_str());

#elif defined(__linux__)
    std::string command = "xdg-open " + url;
    std::system(command.c_str());

#else
#error "Unsupported platform for OpenLink"
#endif
}
