// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief A header including everything
 * @note This is file isn't recommended for production because including it everywhere can increase
 * compile times significantly
 */

#pragma once

// RCore
#include "RCore/Api.hpp"          // IWYU pragma: export
#include "RCore/Conversions.hpp"  // IWYU pragma: export
#include "RCore/Icons.hpp"        // IWYU pragma: export
#include "RCore/Native.hpp"       // IWYU pragma: export
#include "RCore/RApplication.hpp" // IWYU pragma: export
#include "RCore/RContainer.hpp"   // IWYU pragma: export
#include "RCore/RWidget.hpp"      // IWYU pragma: export
#include "RCore/Themes.hpp"       // IWYU pragma: export
#include "RCore/Translations.hpp" // IWYU pragma: export
#include "RCore/Utils.hpp"        // IWYU pragma: export

// Buttons
#include "RWidgets/RButton.hpp"      // IWYU pragma: export
#include "RWidgets/RIconButton.hpp"  // IWYU pragma: export
#include "RWidgets/RLabelButton.hpp" // IWYU pragma: export

// Checkboxes
#include "RWidgets/RCheckbox.hpp" // IWYU pragma: export

// ColorPickers

// Dropdowns

// Images
#include "RWidgets/RImage.hpp" // IWYU pragma: export

// Labels
#include "RWidgets/RLabel.hpp"     // IWYU pragma: export
#include "RWidgets/RLinkLabel.hpp" // IWYU pragma: export

// Layouts
#include "RWidgets/RGridLayout.hpp" // IWYU pragma: export
#include "RWidgets/RHBoxLayout.hpp" // IWYU pragma: export
#include "RWidgets/RLayout.hpp"     // IWYU pragma: export
#include "RWidgets/RVBoxLayout.hpp" // IWYU pragma: export

// Panes
#include "RWidgets/RPane.hpp"        // IWYU pragma: export
#include "RWidgets/RPaneRounded.hpp" // IWYU pragma: export

// ProgressBars
#include "RWidgets/RProgressBar.hpp" // IWYU pragma: export

// ScrollAreas
#include "RWidgets/RScrollArea.hpp" // IWYU pragma: export

// Separators
#include "RWidgets/RBar.hpp" // IWYU pragma: export

// Sliders
#include "RWidgets/RSlider.hpp" // IWYU pragma: export

// Textboxes
#include "RWidgets/RTextbox.hpp"       // IWYU pragma: export
#include "RWidgets/RTextboxDouble.hpp" // IWYU pragma: export
#include "RWidgets/RTextboxInt.hpp"    // IWYU pragma: export

// Windows
#include "RWidgets/ROkCancelWindow.hpp" // IWYU pragma: export
#include "RWidgets/RPopupPane.hpp"      // IWYU pragma: export
#include "RWidgets/RPopupWindow.hpp"    // IWYU pragma: export
#include "RWidgets/RWindow.hpp"         // IWYU pragma: export
