#include "ellipse.h"

Ellipse::Ellipse(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width)
{
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    this->base_line_color = lineColor;
    this->figure_type = FigureType::ellipse;
}

QGraphicsItem* Ellipse::draw()
{
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(QRectF(point1, point2));
    ellipse->setPen(pen);
    if(fill_color != QColor(1, 1, 1)){
        ellipse->setBrush(QBrush(fill_color));
    }
    return ellipse;
}
