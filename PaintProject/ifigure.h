#ifndef IFIGURE_H
#define IFIGURE_H

#include <QGraphicsItem>

class IFigure {
protected:
    QPointF point1;
    QPointF point2;
    QColor lineColor;
    QColor tempLineColor;
    QColor fillColor;
    int width;
    int figureType;
public:
    virtual QGraphicsItem* draw() = 0;
    virtual ~IFigure() = default;
    virtual int getWidth() const = 0;
    virtual void setWidth(int value) = 0;
    virtual QColor getLineColor() const = 0;
    virtual void setLineColor(const QColor &value) = 0;
    virtual QColor getTempLineColor() const = 0;
    virtual void setTempLineColor(const QColor &value) = 0;
    virtual QPointF getPoint1() const = 0;
    virtual QPointF getPoint2() const = 0;
    virtual void setPoint1(const QPointF &value) = 0;
    virtual void setPoint2(const QPointF &value) = 0;
    virtual int getFigureType() const = 0;
    virtual QColor getFillColor() const = 0;
};

#endif // IFIGURE_H

