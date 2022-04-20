#include "Line.h"
#include "Point.h"


std::vector<Dot> Line::draw(Dot dot1, Dot dot2) {
    Point point = Point();
    point.setLineWidth(this->line_width_);
    point.setLineColour(this->line_colour_);

    std::vector<Dot> result;
    int x1 = dot1.getX(), x2 = dot2.getX();
    int y1 = dot1.getY(), y2 = dot2.getY();
    bool changed = false;
    // Bresenham's line algorithm is only good when abs(dx) >= abs(dy)
    // So when abs(dx) < abs(dy), change axis x and y
    if (abs(x2 - x1) < abs(y2 - y1)) {
        int tmp1 = x1;
        x1 = y1;
        y1 = tmp1;
        int tmp2 = x2;
        x2 = y2;
        y2 = tmp2;
        changed = true;
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    int xi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int d = 2 * dy - dx;
    int incrE = dy * 2;
    int incrNE = 2 * dy - 2 * dx;

    int x = x1, y = y1;
    if (changed) {
        auto points = point.draw(Dot{y, x, dot1.getColor()});
        result.insert(result.end(), points.begin(), points.end());
        // result.emplace_back(y, x, dot1.getColor());
    } else {
        auto points = point.draw(Dot{x, y, dot1.getColor()});
        result.insert(result.end(), points.begin(), points.end());
        // result.emplace_back(x, y, dot1.getColor());
    }
    while (x != x2) {
        if (d <= 0)
            d += incrE;
        else {
            d += incrNE;
            y += yi;
        }
        x += xi;
        if (changed) {
            auto points = point.draw(Dot{y, x, dot1.getColor()});
            result.insert(result.end(), points.begin(), points.end());
            // result.emplace_back(y, x, dot1.getColor());
        } else {
            auto points = point.draw(Dot{x, y, dot1.getColor()});
            result.insert(result.end(), points.begin(), points.end());
            // result.emplace_back(x, y, dot1.getColor());
        }
    }
    return result;
}
