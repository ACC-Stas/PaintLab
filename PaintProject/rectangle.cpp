#include "rectangle.h"

Rectangle::Rectangle(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType)
{
    this->point1 = point1;
    this->point2 = point2;
    this->lineColor = lineColor;
    this->fillColor = fillColor;
    this->width = width;
    tempLineColor = lineColor;
    this->figureType = figureType;
}

QGraphicsItem* Rectangle::draw() {
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(width);
    QGraphicsPolygonItem* rectangle = new QGraphicsPolygonItem(QPolygonF(QRectF(point1, point2)));
    rectangle->setPen(pen);
    if(fillColor != QColor(1, 1, 1)){
        rectangle->setBrush(QBrush(fillColor));
    }
    return rectangle;
}

int Rectangle::getWidth() const
{
    return width;
}

void Rectangle::setWidth(int value)
{
    width = value;
}

QColor Rectangle::getLineColor() const
{
    return lineColor;
}

void Rectangle::setLineColor(const QColor &value)
{
    lineColor = value;
}

QColor Rectangle::getTempLineColor() const
{
    return tempLineColor;
}

void Rectangle::setTempLineColor(const QColor &value)
{
    tempLineColor = value;
}

QPointF Rectangle::getPoint2() const
{
    return point2;
}

QPointF Rectangle::getPoint1() const
{
    return point1;
}

void Rectangle::setPoint2(const QPointF &value)
{
    point2 = value;
}

void Rectangle::setPoint1(const QPointF &value)
{
    point1 = value;
}

QColor Rectangle::getFillColor() const
{
    return fillColor;
}

int Rectangle::getFigureType() const
{
    return figureType;
}
