#include "polygon.h"

Polygon::Polygon(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType) {
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = lineColor;
    this->fill_color = fillColor;
    this->width = width;
    base_line_color = lineColor;
    this->figure_type = figureType;
}

QGraphicsItem* Polygon::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QGraphicsPolygonItem* polygon = new QGraphicsPolygonItem(QPolygonF(QVector<QPointF>{point1, point2}));
    polygon->setPen(pen);
    if(fill_color != QColor(1, 1, 1)){
        polygon->setBrush(QBrush(fill_color));
    }
    return polygon;
}
