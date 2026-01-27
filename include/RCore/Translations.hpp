// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief Functions for translations
 */

#pragma once

#include <filesystem>
#include <string>

/**
 * @brief An std::string wrapper for libintl-lite's gettext
 *
 * @param id The id for the target string (usually in English)
 * @return std::string
 */
std::string GetText(const std::string& id);

/**
 * @brief Set the language
 *
 * @param domain The name of the .mo file
 * @param localePath A path for locales
 * @param language The target language
 * @note This funcitons requires a specific file layout:
 * @p localePath / @p language / LC_MESSAGES / @p domain .mo
 * @see GetText
 */
void SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                 const std::string& language);
