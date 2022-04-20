#pragma once

#include "Figures/Drawable.h"
#include "Figures/Point.h"
#include "Figures/Line.h"
#include "Figures/Rectangle.h"
#include <memory>
#include <unordered_set>
#include <unordered_map>

enum class DrawerNames {
    point = 1,
    line = 2,
    rectangle = 3,
    ellipse = 4,
    brush = 5
};

class Drawer {
public:
    Drawer();

    std::vector<Dot> draw(const Dot &dot1, const Dot &dot2);

    void setDrawer(const DrawerNames &name);

    void setLineWidth(int width);

    void setLineColour(Colour colour);

    void setMainColour(Colour colour);

    static const std::unordered_set<DrawerNames> one_clickable;

    bool isOneClickable() const;

private:
    int line_width_;
    Colour line_colour_{}, main_colour_{};
    DrawerNames name_;
    std::unordered_map<DrawerNames, std::unique_ptr<Drawable>> map_;
};