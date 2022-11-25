#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Rectangle : public IFigure
{
public:
    Rectangle(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width);
    QGraphicsItem* draw() override;
};

#endif // RECTANGLE_H
