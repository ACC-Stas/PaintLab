#include "polygon.h"

Polygon::Polygon(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width) {
    this->point1 = point1;
    this->point2 = point2;
    this->line_color = line_color;
    this->fill_color = fill_color;
    this->width = width;
    base_line_color = line_color;
    this->figure_type = FigureType::polygon;
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
