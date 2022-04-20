#pragma once

#include "Dot.h"
#include <vector>

class Drawable {
public:
    virtual std::vector<Dot> draw(Dot dot1, Dot dot2) = 0;

    virtual void setLineWidth(int width) {
        line_width_ = width;
    }

    virtual void setLineColour(Colour colour) {
        line_colour_ = colour;
    }

    virtual void setMainColour(Colour colour) {
        main_colour_ = colour;
    }

    virtual ~Drawable() = default;

protected:
    Colour line_colour_{};
    Colour main_colour_{};
    int line_width_{};
};