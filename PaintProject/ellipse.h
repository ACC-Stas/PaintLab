#ifndef ELLIPSE_H
#define ELLIPSE_H


#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Ellipse : public IFigure {
public:
    Ellipse(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width);
    QGraphicsItem* draw() override;
};

#endif // ELLIPSE_H
