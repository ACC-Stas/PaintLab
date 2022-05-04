#include "polygon.h"

Polygon::Polygon(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType)
{
    this->point1 = point1;
    this->point2 = point2;
    this->lineColor = lineColor;
    this->fillColor = fillColor;
    this->width = width;
    tempLineColor = lineColor;
    this->figureType = figureType;
}

QGraphicsItem* Polygon::draw()
{
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(width);
    QGraphicsPolygonItem* polygon = new QGraphicsPolygonItem(QPolygonF(QVector<QPointF>{point1, point2}));
    polygon->setPen(pen);
    if(fillColor != QColor(1, 1, 1)){
        polygon->setBrush(QBrush(fillColor));
    }
    return polygon;
}

int Polygon::getWidth() const
{
    return width;
}

void Polygon::setWidth(int value)
{
    width = value;
}

QColor Polygon::getLineColor() const
{
    return lineColor;
}

void Polygon::setLineColor(const QColor &value)
{
    lineColor = value;
}

QColor Polygon::getTempLineColor() const
{
    return tempLineColor;
}

void Polygon::setTempLineColor(const QColor &value)
{
    tempLineColor = value;
}

QPointF Polygon::getPoint2() const
{
    return point2;
}

QPointF Polygon::getPoint1() const
{
    return point1;
}

void Polygon::setPoint2(const QPointF &value)
{
    point2 = value;
}

void Polygon::setPoint1(const QPointF &value)
{
    point1 = value;
}

QColor Polygon::getFillColor() const
{
    return fillColor;
}

int Polygon::getFigureType() const
{
    return figureType;
}
