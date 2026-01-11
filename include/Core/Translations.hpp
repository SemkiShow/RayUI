// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include <filesystem>
#include <string>

std::string GetText(const std::string& id);
void SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                 const std::string& language);
