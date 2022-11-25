#include "line.h"

Line::Line(std::vector<QPointF> points, QColor lineColor, QColor fillColor, int width) {
    this->points = points;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    this->base_line_color = lineColor;
    this->figure_type = FigureType("line");
}

QGraphicsItem* Line::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QGraphicsLineItem* line = new QGraphicsLineItem(points[0].x(), points[0].y(), points[1].x(), points[1].y());
    line->setPen(pen);
    return line;
}
