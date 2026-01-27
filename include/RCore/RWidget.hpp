// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT
/**
 * @file
 * @brief @copydoc RWidget
 * @defgroup RWidget
 * @brief Widgets
 * @{
 */

#pragma once

#include "RCore/Themes.hpp"
#include "RCore/Utils.hpp"
#include <memory>

/**
 * @brief The main widget class
 */
class RWidget
{
  public:
    virtual ~RWidget() = default;

    virtual void ResetEvents();
    virtual bool PollEvents();
    virtual void Shrink() {}
    virtual void Update();
    virtual void Draw() {}

    virtual void UpdateLabels() {}

    void SetBounds(RRectangle rec) { bounds = rec; }
    void SetPosition(RVector2 vec) { bounds.SetPosition(vec); }
    void SetPositionX(float val) { bounds.x = val; }
    void SetPositionY(float val) { bounds.y = val; }
    void SetSize(RVector2 vec) { bounds.SetSize(vec); }
    void SetWidth(float val) { bounds.width = val; }
    void SetHeight(float val) { bounds.height = val; }

    RRectangle GetBounds() { return bounds; }
    RVector2 GetPosition() { return bounds.GetPosition(); }
    float GetPositionX() { return bounds.x; }
    float GetPositionY() { return bounds.y; }
    RVector2 GetSize() { return bounds.GetSize(); }
    float GetWidth() { return bounds.width; }
    float GetHeight() { return bounds.height; }

    void SetMinSize(RVector2 vec) { minSize = vec; }
    void SetMinWidth(float val) { minSize.x = val; }
    void SetMinHeight(float val) { minSize.y = val; }

    RVector2 GetMinSize() { return minSize; }
    float GetMinWidth() { return minSize.x; }
    float GetMinHeight() { return minSize.y; }

    void SetMaxSize(RVector2 vec) { maxSize = vec; }
    void SetMaxWidth(float val) { maxSize.x = val; }
    void SetMaxHeight(float val) { maxSize.y = val; }

    RVector2 GetMaxSize() { return maxSize; }
    float GetMaxWidth() { return maxSize.x; }
    float GetMaxHeight() { return maxSize.y; }

    /**
     * @brief Flags widget for a bounds update
     * @note The bounds are actually updated on the next Update() call
     * @see Update
     */
    void UpdateBounds() { updateBounds = true; }

    void SetVisible(bool val)
    {
        visible = val;
        if (visible) UpdateBounds();
    }

    bool IsVisible() { return visible; }

    /**
     * @brief Set the widget's alignment
     * @note Has to be called separately for vertical and horizontal alignment
     * @param flag
     */
    void SetAlignment(RAlign flag)
    {
        if (flag == RAlign::Left || flag == RAlign::HCenter || flag == RAlign::Right) alignH = flag;
        if (flag == RAlign::Top || flag == RAlign::VCenter || flag == RAlign::Bottom) alignV = flag;
    }

    RAlign GetAlignH() { return alignH; }
    RAlign GetAlignV() { return alignV; }

    virtual void SetFont(std::shared_ptr<RFont> ptr)
    {
        font = ptr;
        UpdateBounds();
    }

    std::shared_ptr<RFont> GetFont() { return font; }

    void SetFontSpacing(float val)
    {
        fontSpacing = val;
        UpdateBounds();
    }

    float GetFontSpacing() { return fontSpacing; }

    virtual void SetTheme(std::shared_ptr<RTheme> val) { theme = val; }

    void SetThemeList(RThemeList val)
    {
        themeList = val;
        customColor = false;
    }

    void SetTint(RColor val)
    {
        tint = val;
        customColor = true;
    }

    std::shared_ptr<RTheme> GetTheme() { return theme; }

    RThemeList GetThemeList() { return themeList; }

    RThemeState GetThemeState() { return themeState; }

    RColor GetThemeColor()
    {
        return theme->colors[static_cast<int>(themeList)][static_cast<int>(themeState)];
    }

    RColor GetThemeColor(RThemeList list, RThemeState state)
    {
        return theme->colors[static_cast<int>(list)][static_cast<int>(state)];
    }

    bool IsCustomColor() { return customColor; }

    RColor GetColor() { return color; }

    RColor GetTint() { return tint; }

    void SetDisabled(bool val) { disabled = val; }

    bool IsDisabled() { return disabled; }

    void SetHighlighted(bool val) { highlighted = val; }

    bool IsHighlighted() { return highlighted; }

    void SetDrawBorder(bool val) { drawBorder = val; }

    bool IsDrawBorder() { return drawBorder; }

    void SetBorderThickness(float val) { borderThickness = val; }

    float GetBorderThickness() { return borderThickness; }

    void UpdateColors();

    virtual void SetScale(float val)
    {
        float delta = val / scale;
        if (minSize.x >= 0) minSize.x *= delta;
        if (minSize.y >= 0) minSize.y *= delta;
        if (maxSize.x >= 0) maxSize.x *= delta;
        if (maxSize.y >= 0) maxSize.y *= delta;
        borderThickness *= delta;
        scale = val;
        UpdateBounds();
    }

    float GetScale() { return scale; }

    void SetAnimated(bool val) { isAnimated = val; }
    void SetHoverable(bool val) { isHoverable = val; }
    void SetClickable(bool val) { isClickable = val; }

    bool IsAnimated() { return isAnimated; }
    bool IsHoverable() { return isHoverable; }
    bool IsClickable() { return isClickable; }

    virtual void SetDebugMode(bool val) { debugMode = val; }

    bool IsDebugMode() { return debugMode; }

    virtual void DrawDebugOutline();

    void DeleteLater() { deleteLater = true; }

    bool IsDeleteLater() { return deleteLater; }

    bool IsMouseHovered() { return isMouseHovered; }
    bool IsMouseLeftDown() { return isMouseLeftDown; }
    bool IsMouseLeftPressed() { return isMouseLeftPressed; }
    bool IsMouseLeftReleased() { return isMouseLeftReleased; }
    bool IsMouseRightDown() { return isMouseRightDown; }
    bool IsMouseRightPressed() { return isMouseRightPressed; }
    bool IsMouseRightReleased() { return isMouseRightReleased; }

  protected:
    bool updateBounds = false;
    /**
     * @brief The widget's current bounds
     */
    RRectangle bounds{0, 0, -1, -1};
    /**
     * @brief The minimal size of the widget
     * @note Negative values mean no min limit (the size can be negative)
     */
    RVector2 minSize{30, 30};
    /**
     * @brief The maximum size of the widget
     * @note Negative values mean that the widget can expand in that axis
     */
    RVector2 maxSize{-1, -1};
    bool visible = true;
    RAlign alignH = RAlign::Left, alignV = RAlign::Top;
    std::shared_ptr<RFont> font;
    float fontSpacing = 0;
    std::shared_ptr<RTheme> theme = std::make_shared<RThemeLight>();
    RThemeList themeList = RThemeList::Primary;
    RThemeState themeState = RThemeState::Default;
    RColor color = GetThemeColor(), tint;
    bool customColor = false;
    bool disabled = false, highlighted = false;
    bool drawBorder = true;
    float borderThickness = 2;
    float scale = 1;
    bool isAnimated = true, isHoverable = true, isClickable = true;
    bool debugMode = false;
    bool deleteLater = false;

  private:
    bool isMouseHovered = false, isMouseLeftDown = false, isMouseLeftPressed = false,
         isMouseLeftReleased = false, isMouseRightDown = false, isMouseRightPressed = false,
         isMouseRightReleased = false;
};
