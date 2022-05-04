#include "line.h"

Line::Line(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType) {
    this->point1 = point1;
    this->point2 = point2;
    this->lineColor = lineColor;
    this->fillColor = fillColor;
    this->width = width;
    tempLineColor = lineColor;
    this->figureType = figureType;
}

QGraphicsItem* Line::draw() {
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(width);
    QGraphicsLineItem* line = new QGraphicsLineItem(point1.x(), point1.y(), point2.x(), point2.y());
    line->setPen(pen);
    return line;
}

int Line::getWidth() const {
    return width;
}

void Line::setWidth(int value) {
    width = value;
}

QColor Line::getLineColor() const {
    return lineColor;
}

void Line::setLineColor(const QColor &value) {
    lineColor = value;
}

QColor Line::getTempLineColor() const {
    return tempLineColor;
}

void Line::setTempLineColor(const QColor &value) {
    tempLineColor = value;
}

QPointF Line::getPoint2() const {
    return point2;
}

QPointF Line::getPoint1() const {
    return point1;
}

void Line::setPoint2(const QPointF &value)
{
    point2 = value;
}

void Line::setPoint1(const QPointF &value)
{
    point1 = value;
}

QColor Line::getFillColor() const
{
    return fillColor;
}

int Line::getFigureType() const
{
    return figureType;
}
