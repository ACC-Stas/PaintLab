#include "polygon.h"

Polygon::Polygon(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) {
    this->points = points;
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

    QVector<QPointF> qpoints;
    for (const auto& point : points) {
        qpoints << point;
    }

    QGraphicsPolygonItem* polygon = new QGraphicsPolygonItem(QPolygonF(qpoints));
    polygon->setPen(pen);
    if(fill_color != QColor(1, 1, 1)){
        polygon->setBrush(QBrush(fill_color));
    }
    return polygon;
}
