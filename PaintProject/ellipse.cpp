#include "ellipse.h"

Ellipse::Ellipse(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType)
{
    this->point1 = point1;
    this->point2 = point2;
    this->lineColor = lineColor;
    this->fillColor = fillColor;
    this->width = width;
    tempLineColor = lineColor;
    this->figureType = figureType;
}

QGraphicsItem* Ellipse::draw()
{
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(width);
    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(QRectF(point1, point2));
    ellipse->setPen(pen);
    if(fillColor != QColor(1, 1, 1)){
        ellipse->setBrush(QBrush(fillColor));
    }
    return ellipse;
}

int Ellipse::getWidth() const
{
    return width;
}

void Ellipse::setWidth(int value)
{
    width = value;
}

QColor Ellipse::getLineColor() const
{
    return lineColor;
}

void Ellipse::setLineColor(const QColor &value)
{
    lineColor = value;
}

QColor Ellipse::getTempLineColor() const
{
    return tempLineColor;
}

void Ellipse::setTempLineColor(const QColor &value)
{
    tempLineColor = value;
}

QPointF Ellipse::getPoint2() const
{
    return point2;
}

QPointF Ellipse::getPoint1() const
{
    return point1;
}

void Ellipse::setPoint2(const QPointF &value)
{
    point2 = value;
}

void Ellipse::setPoint1(const QPointF &value)
{
    point1 = value;
}

QColor Ellipse::getFillColor() const
{
    return fillColor;
}

int Ellipse::getFigureType() const
{
    return figureType;
}
