#pragma once

#include "Figures/Drawable.h"
#include "unordered_map"
#include "Figures/Point.h"
#include "Figures/Line.h"
#include "Figures/Rectangle.h"
#include <memory>

class Drawer {
public:
    Drawer();

    std::vector<Dot> draw(const Dot &dot1, const Dot &dot2);

    void setDrawer(const std::string &name);

    void setLineWidth(int width);

    void setLineColour(Colour colour);

    void setMainColour(Colour colour);

private:
    int line_width_;
    Colour line_colour_{}, main_colour_{};
    std::string name_;
    std::unordered_map<std::string, std::unique_ptr<Drawable>> map_;
};
