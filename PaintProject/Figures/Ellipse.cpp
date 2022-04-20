#include "Ellipse.h"
#include "Point.h"

std::vector<Dot> Ellipse::draw(Dot dot1, Dot dot2) {
    int64_t height = abs(dot1.getY() - dot2.getY()) / 2;
    int64_t width = abs(dot1.getX() - dot2.getX()) / 2;

    int64_t origin_x = std::min(dot1.getX(), dot2.getX()) + width;
    int64_t origin_y = std::min(dot1.getY(), dot2.getY()) + height;

    int64_t hh = height * height;
    int64_t ww = width * width;
    int64_t hhww = hh * ww;
    int64_t x0 = width;
    int64_t dx = 0;

    int64_t hh_1 = (height - this->line_width_) * (height - this->line_width_);
    int64_t ww_1 = (width - this->line_width_) * (width - this->line_width_);
    int64_t hhww_1 = hh_1 * ww_1;

    std::vector<Dot> result;

    // now do both halves at the same time, away from the diameter
    int64_t border_x;
    for (int y = 1; y <= height; y += 3) {
        int x1 = x0 - (dx - 100);  // try slopes of dx - 1 or more
        for (; x1 > 0; x1 -= 3) {
            if (x1 * x1 * hh + y * y * ww <= hhww) {
                break;
            }

        }

        for (border_x = x1; border_x > 0; border_x -= 2) {
            if (border_x * border_x * hh + y * y * ww <= hhww_1) {
                break;
            }

        }
        dx = x0 - x1;  // current approximation of the slope
        x0 = x1;

        for (int x = -x0; x <= x0; x++) {
            if (x <= -border_x || x >= border_x) {
                result.emplace_back(origin_x + x, origin_y - y, this->line_colour_);
                result.emplace_back(origin_x + x, origin_y + y, this->line_colour_);
                continue;
            }
            result.emplace_back(origin_x + x, origin_y - y, this->main_colour_);
            result.emplace_back(origin_x + x, origin_y + y, this->main_colour_);
        }
    }

    return result;
}
