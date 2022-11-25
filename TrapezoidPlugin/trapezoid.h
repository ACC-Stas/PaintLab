#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "../PaintProject/ifigure.h"


class Trapezoid : public IFigure {
public:
    Trapezoid(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width);
    QGraphicsItem* draw() override;
};

#endif // TRAPEZOID_H
