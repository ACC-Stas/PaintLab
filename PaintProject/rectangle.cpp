#include "rectangle.h"

Rectangle::Rectangle(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width)
{
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = line_color;
    this->fill_color = fill_color;
    this->width = width;
    this->base_line_color = line_color;
    this->figure_type = FigureType::rectangle;
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
