#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Rectangle : public IFigure
{
public:
    Rectangle(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width, int figure_type);
    QGraphicsItem* draw() override;
};

#endif // RECTANGLE_H
