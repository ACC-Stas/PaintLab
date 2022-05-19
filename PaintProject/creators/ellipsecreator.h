#ifndef ELLIPSECREATOR_H
#define ELLIPSECREATOR_H

#include "ICreator.h"
#include "ellipse.h"

class EllipseCreator : public ICreator {
public:
    EllipseCreator() {
        this->figureType = FigureType("ellipse");
    }

    IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) override {
        return new Ellipse(points, line_color, fill_color, width);
    }
};

#endif // ELLIPSECREATOR_H
