#ifndef RECTANGLECREATOR_H
#define RECTANGLECREATOR_H

#include "ICreator.h"
#include "rectangle.h"

class RectangleCreator : public ICreator {
public:

    RectangleCreator() {
        this->figureType = FigureType("rectangle");
    }

    IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) override {
        return new Rectangle(points, line_color, fill_color, width);
    }
};

#endif // RECTANGLECREATOR_H
