#ifndef POLYGONCREATOR_H
#define POLYGONCREATOR_H

#include "ICreator.h"
#include "polygon.h"

class PolygonCreator : public ICreator {
public:
    PolygonCreator() {
        this->figureType = FigureType("polygon");
    }

    IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) override {
        return new Polygon(points, line_color, fill_color, width);
    }
};

#endif // POLYGONCREATOR_H
