// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include <RayUI.hpp>
#include <iostream>

int main()
{
    ShowPopupNotification("RayUI Native Functions Example", "Test notification", IconType::Info);

    auto res = ShowMessageBox("Question", "Would you like to continue?", DialogType::YesNo,
                              IconType::Info, DialogButton::Yes);
    if (res == DialogButton::No) return 0;

#ifndef _WIN32
    std::cout << "Username: " << ShowInputBox("Info", "Input the username", "") << '\n';
    std::cout << "Password: " << ShowInputBox("Info", "Input the password", "", true) << '\n';
#endif

    std::cout << "Saved file " << ShowSaveFileDialog("Save a file", ".", {}, "") << '\n';

    std::cout << "Opened file ";
    for (auto& file: ShowOpenFileDialog("Open files", ".", {}, "", false))
    {
        std::cout << file << ' ';
    }
    std::cout << '\n';

    std::cout << "Opened files: ";
    for (auto& file: ShowOpenFileDialog("Open files", ".", {}, "", true))
    {
        std::cout << file << ' ';
    }
    std::cout << '\n';

    std::cout << "Selected folder " << ShowSelectFolderDialog("Select a folder", ".") << '\n';

    {
        auto color = ShowColorPicker("Pick a color", "#FF0000");
        std::cout << "Picked color " << std::to_string(color.r) << ' ' << std::to_string(color.g)
                  << ' ' << std::to_string(color.b) << '\n';
    }

    {
        unsigned char defaultColor[3] = {0, 255, 0};
        auto color = ShowColorPicker("Pick a color", defaultColor);
        std::cout << "Picked color " << std::to_string(color.r) << ' ' << std::to_string(color.g)
                  << ' ' << std::to_string(color.b) << '\n';
    }

    std::cout << "Picked color " << ShowColorPickerHex("Pick a color", "#0000FF") << '\n';

    {
        unsigned char defaultColor[3] = {255, 255, 255};
        std::cout << "Picked color " << ShowColorPickerHex("Pick a color", defaultColor) << '\n';
    }

    return 0;
}
