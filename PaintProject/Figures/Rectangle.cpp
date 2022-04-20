#include "Rectangle.h"
#include "Point.h"


std::vector<Dot> Rectangle::draw(Dot dot1, Dot dot2) {
    Line line = Line();
    line.setLineColour(this->line_colour_);
    line.setLineWidth(this->line_width_);
    line.setMainColour(this->main_colour_);

    std::vector<Dot> result;
    int x1 = dot1.getX(), x2 = dot2.getX();
    int y1 = dot1.getY(), y2 = dot2.getY();

    Dot left_up = Dot{std::min(x1, x2), std::max(y1, y2), this->line_colour_};
    Dot right_up = Dot{std::max(x1, x2), std::max(y1, y2), this->line_colour_};

    Dot left_down = Dot{std::min(x1, x2), std::min(y1, y2), this->line_colour_};
    Dot right_down = Dot{std::max(x1, x2), std::min(y1, y2), this->line_colour_};

    auto points1 = line.draw(left_up, right_up);
    auto points2 = line.draw(right_up, right_down);
    auto points3 = line.draw(right_down, left_down);
    auto points4 = line.draw(left_down, left_up);

    result.insert(result.end(), points1.begin(), points1.end());
    result.insert(result.end(), points2.begin(), points2.end());
    result.insert(result.end(), points3.begin(), points3.end());
    result.insert(result.end(), points4.begin(), points4.end());

    for (int x = left_up.getX() + this->line_width_; x < right_up.getX() - this->line_width_; x += 3) {
        for (int y = left_down.getY() + this->line_width_; y < left_up.getY() - this->line_width_; y += 3) {
            result.emplace_back(x, y, this->main_colour_);
        }
    }

    return result;
}
