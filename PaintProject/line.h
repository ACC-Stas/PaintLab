#ifndef LINE_H
#define LINE_H

#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Line : public IFigure {
public:
    Line(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width, int figure_type);
    QGraphicsItem* draw() override;
};

#endif // LINE_H
