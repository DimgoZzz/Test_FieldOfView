#pragma once
#include "DataClasses.h"

class Box
{
public:
    float left;
    float top;
    float width; 
    float height;

    Box(float Left = 0, float Top = 0, float Width = 0, float Height = 0) noexcept :
        left(Left), top(Top), width(Width), height(Height)
    {

    }

    Box(const FloatPoint& position, const FloatPoint& size) noexcept :
        left(position.GetX()), top(position.GetY()), width(size.GetX()), height(size.GetY())
    {

    }

    inline float GetRight() const noexcept
    {
        return left + width;
    }

    inline float GetBottom() const noexcept
    {
        return top + height;
    }

    FloatPoint GetTopLeft() const noexcept
    {
        return FloatPoint(left, top);
    }

    FloatPoint GetCenter() const noexcept
    {
        return FloatPoint(left + width / 2, top + height / 2);
    }

    FloatPoint GetSize() const noexcept
    {
        return FloatPoint(width, height);
    }

    bool ContainsBox(const Box& box) const noexcept
    {
        return left <= box.left && box.GetRight() <= GetRight() &&
            top <= box.top && box.GetBottom() <= GetBottom();
    }

    bool IntersectsBox(const Box& box) const noexcept
    {
        return !(left >= box.GetRight() || GetRight() <= box.left ||
            top >= box.GetBottom() || GetBottom() <= box.top);
    }
};