#ifndef POLYGON_H
#define POLYGON_H

#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Polygon : public IFigure {
public:
    Polygon(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width);
    QGraphicsItem* draw() override;
};

#endif // POLYGON_H
