#ifndef IFIGURE_H
#define IFIGURE_H

#include <QGraphicsItem>
#include "figuretype.h"

class IFigure {
protected:
    QPointF point1;
    QPointF point2;
    QColor line_color;
    QColor base_line_color;
    QColor fill_color;
    int width;
    FigureType figure_type;

public:
    virtual QGraphicsItem* draw() = 0;
    virtual ~IFigure() = default;
    virtual int getWidth() const {
        return width;
    }
    virtual void setWidth(int value) {
        width = value;
    }
    virtual QColor getLineColor() {
        return line_color;
    }
    virtual void setLineColor(const QColor &value) {
        line_color = value;
    }
    virtual QColor getTempLineColor() const {
        return base_line_color;
    }
    virtual void setTempLineColor(const QColor &value) {
        base_line_color = value;
    }
    virtual QPointF getPoint1() const {
        return point1;
    }
    virtual QPointF getPoint2() const {
        return point2;
    }
    virtual void setPoint1(const QPointF &value) {
        point1 = value;
    }
    virtual void setPoint2(const QPointF &value) {
        point2 = value;
    }
    virtual FigureType getFigureType() const {
        return figure_type;
    }
    virtual QColor getFillColor() const {
        return fill_color;
    }
};

#endif // IFIGURE_H

