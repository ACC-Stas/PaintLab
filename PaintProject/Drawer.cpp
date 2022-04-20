#include "Drawer.h"

void Drawer::setMainColour(Colour colour) {
    main_colour_ = colour;
}

void Drawer::setLineColour(Colour colour) {
    line_colour_ = colour;
}

void Drawer::setLineWidth(int width) {
    line_width_ = width;
}

void Drawer::setDrawer(const std::string &name) {
    if (map_.find(name) == map_.end()) {
        throw std::runtime_error("Invalid name " + name);
    }

    name_ = name;
}

std::vector<Dot> Drawer::draw(const Dot &dot1, const Dot &dot2) {
    map_[name_]->setLineColour(line_colour_);
    map_[name_]->setMainColour(main_colour_);
    map_[name_]->setLineWidth(line_width_);

    return map_[name_]->draw(dot1, dot2);
}

Drawer::Drawer() {
    line_width_ = 1;
    line_colour_ = Colour{1.0, 1.0, 1.0};
    main_colour_ = Colour{1.0, 1.0, 1.0};
    name_ = "point";
    map_["point"] = std::make_unique<Point>();
    map_["line"] = std::make_unique<Line>();
    map_["rectangle"] = std::make_unique<Rectangle>();
}
