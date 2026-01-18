// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#include "RCore/Translations.hpp"
#include <libintl.h>

std::string GetText(const std::string& id) { return std::string(gettext(id.c_str())); }

void SetLanguage(const std::string& domain, const std::filesystem::path& localePath,
                 const std::string& language)
{
#ifdef _WIN32
    _putenv(("LANGUAGE=" + language).c_str());
#else
    setenv("LANGUAGE", language.c_str(), 1);
#endif
    bindtextdomain(domain.c_str(), localePath.c_str());
    textdomain(domain.c_str());
}
