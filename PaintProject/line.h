#ifndef LINE_H
#define LINE_H

#pragma once
#include "ifigure.h"
#include <vector>
#include <QPen>

class Line : public IFigure {
public:
    Line(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width);
    QGraphicsItem* draw() override;
};

#endif // LINE_H
