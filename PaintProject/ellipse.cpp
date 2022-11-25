#include "ellipse.h"

Ellipse::Ellipse(std::vector<QPointF> points, QColor lineColor, QColor fillColor, int width) {
    this->points = points;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    this->base_line_color = lineColor;
    this->figure_type = FigureType("ellipse");
}

QGraphicsItem* Ellipse::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(QRectF(points[0], points[1]));
    ellipse->setPen(pen);
    if(fill_color != QColor(1, 1, 1)) {
        ellipse->setBrush(QBrush(fill_color));
    }
    return ellipse;
}
