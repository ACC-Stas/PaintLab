#include "factory.h"
#include <memory>

#include <line.h>
#include <rectangle.h>
#include <ellipse.h>
#include <polygon.h>

IFigure* Factory::createFigure(QPointF point1, QPointF point2, QColor line_color, QColor fill_color, int width, FigureType figure_type) {
    switch (figure_type) {
    case FigureType::line: {
        return new Line(point1, point2, line_color, fill_color, width);
    }
    case FigureType::ellipse: {
        return new Ellipse(point1, point2, line_color, fill_color, width);
    }

    case FigureType::rectangle: {
        return new Rectangle(point1, point2, line_color, fill_color, width);
    }
    case FigureType::polyline: {
        return new Line(point1, point2, line_color, fill_color, width);
    }
    case FigureType::polygon: {
        return new Polygon(point1, point2, line_color, fill_color, width);
    }

    }
}
