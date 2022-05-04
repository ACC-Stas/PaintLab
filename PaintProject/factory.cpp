#include "factory.h"
#include <memory>

#include <line.h>
#include <rectangle.h>
#include <ellipse.h>
#include <polygon.h>

IFigure* Factory::createFigure(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width, FigureType figure_type) {
    switch (figure_type) {
    case FigureType::line: {
        return new Line(points, line_color, fill_color, width);
    }
    case FigureType::ellipse: {
        return new Ellipse(points, line_color, fill_color, width);
    }

    case FigureType::rectangle: {
        return new Rectangle(points, line_color, fill_color, width);
    }
    case FigureType::polyline: {
        return new Line(points, line_color, fill_color, width);
    }
    case FigureType::polygon: {
        return new Polygon(points, line_color, fill_color, width);
    }

    }
}
