#include "trapezoid.h"
#include <QtWidgets>

Trapezoid::Trapezoid(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) {
    this->points = points;
    this->line_color = line_color;
    this->fill_color = fill_color;
    this->width = width;
    base_line_color = line_color;
    this->figure_type = FigureType("trapezoid");
}

QGraphicsItem* Trapezoid::draw() {
    QPen pen;
    pen.setColor(line_color);
    pen.setWidth(width);
    QPointF upper_point, low_point;
    QPointF right_point, left_point;
    if (points[0].y() > points[1].y()) {
        upper_point = points[0];
        low_point = points[1];
    } else {
        upper_point = points[1];
        low_point = points[0];
    }

    if (points[0].x() > points[1].x()) {
        left_point = points[1];
        right_point = points[0];
    } else {
        left_point = points[0];
        right_point = points[1];
    }



    QPointF point1, point2, point3, point4;

    point1.setX((right_point.x() - left_point.x()) / 4 + left_point.x());
    point2.setX(-(right_point.x() - left_point.x()) / 4 + right_point.x());
    point1.setY(upper_point.y());
    point2.setY(upper_point.y());

    point3.setX(right_point.x());
    point3.setY(low_point.y());
    point4.setX(left_point.x());
    point4.setY(low_point.y());

    QVector<QPointF> qpoints;
    qpoints << point1;
    qpoints << point2;
    qpoints << point3;
    qpoints << point4;

    QGraphicsPolygonItem* polygon = new QGraphicsPolygonItem(QPolygonF(qpoints));
    polygon->setPen(pen);
    if(fill_color != QColor(1, 1, 1)) {
        polygon->setBrush(QBrush(fill_color));
    }
    return polygon;
}
