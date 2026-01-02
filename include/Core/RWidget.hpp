// SPDX-FileCopyrightText: 2026 SemkiShow
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Utils.hpp"

class RWidget
{
  public:
    virtual ~RWidget() = default;

    virtual void Update();
    virtual void Draw() {}

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

    void UpdateBounds() { updateBounds = true; }

  protected:
    bool updateBounds = false;
    RRectangle bounds{0, 0, -1, -1};
    RVector2 minSize{10, 10};
    RVector2 maxSize{-1, -1};
};
