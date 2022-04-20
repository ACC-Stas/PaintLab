#include "RadialBrush.h"
#include "Point.h"

std::vector<Dot> RadialBrush::draw(Dot dot1, Dot dot2) {
    int x = dot1.getX(), y = dot1.getY();

    Point point = Point();
    point.setLineWidth(1);
    point.setLineColour(this->line_colour_);
    point.setMainColour(this->main_colour_);

    std::vector<Dot> result;

    for (int i = 0; i < this->line_width_; i++) {
        int rand_x = rand() % (this->line_width_ + 1) - this->line_width_ / 2 + x;
        int rand_y = rand() % (this->line_width_ + 1) - this->line_width_ / 2 + y;

        auto points = point.draw(Dot{rand_x, rand_y, this->line_colour_});
        result.insert(result.end(), points.begin(), points.end());
    }

    return result;
}
