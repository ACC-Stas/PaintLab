#include "Point.h"

std::vector<Dot> Point::draw(Dot dot1, Dot dot2) {
    std::vector<Dot> result;
    for (int i = dot1.getX() - line_width_; i < dot1.getX() + line_width_; ++i) {
        for (int j = dot1.getY() - line_width_; j < dot1.getY() + line_width_; ++j) {
            result.emplace_back(i, j, this->line_colour_);
        }
    }
    return result;
}
