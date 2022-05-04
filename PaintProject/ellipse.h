#ifndef ELLIPSE_H
#define ELLIPSE_H


#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Ellipse : public IFigure
{
public:
    Ellipse(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width, int figure_type);
    QGraphicsItem* draw() override;
};

#endif // ELLIPSE_H
