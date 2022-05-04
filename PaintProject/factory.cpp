#include "factory.h"

IFigure* factory::createFigure(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType) {
    switch(figureType) {
    case 1:
        return new Line(point1, point2, lineColor, fillColor, width, figureType);
        break;
    case 2:
        return new Rectangle(point1, point2, lineColor, fillColor, width, figureType);
        break;
    case 3:
        return new Ellipse(point1, point2, lineColor, fillColor, width, figureType);
        break;
    case 4:
        return new Polygon(point1, point2, lineColor, fillColor, width, figureType);
        break;
    default:
        return new Line(point1, point2, lineColor, fillColor, width, figureType);
        break;
    }
}
