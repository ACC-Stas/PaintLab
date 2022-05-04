#include "rectangle.h"

Rectangle::Rectangle(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType)
{
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    base_line_color = lineColor;
    this->figure_type = figureType;
}

QGraphicsItem* Rectangle::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);

    QGraphicsPolygonItem* rectangle = new QGraphicsPolygonItem(QPolygonF(QRectF(point1, point2)));
    rectangle->setPen(pen);
    if(fill_color != QColor(1, 1, 1)){
        rectangle->setBrush(QBrush(fill_color));
    }
    return rectangle;
}
