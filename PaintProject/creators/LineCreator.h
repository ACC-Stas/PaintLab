#ifndef LINECREATOR_H
#define LINECREATOR_H

#include "ICreator.h"
#include "line.h"

class LineCreator : public ICreator {
public:
    LineCreator() {
        this->figureType = FigureType("line");
    }

    IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) override {
        return new Line(points, line_color, fill_color, width);
    }
};

#endif // LINECREATOR_H
