#include "line.h"

Line::Line(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType) {
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    base_line_color = lineColor;
    this->figure_type = figureType;
}

QGraphicsItem* Line::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QGraphicsLineItem* line = new QGraphicsLineItem(point1.x(), point1.y(), point2.x(), point2.y());
    line->setPen(pen);
    return line;
}
