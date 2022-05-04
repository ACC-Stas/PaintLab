#ifndef IFIGURE_H
#define IFIGURE_H

#include <QGraphicsItem>
#include <vector>
#include "figuretype.h"

class IFigure {
protected:
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

    virtual FigureType getFigureType() const {
        return figure_type;
    }
    virtual QColor getFillColor() const {
        return fill_color;
    }

    std::vector<QPointF> points;
};

#endif // IFIGURE_H

