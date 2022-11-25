#include "factory.h"
#include <memory>

#include <line.h>
#include <rectangle.h>
#include <ellipse.h>
#include <polygon.h>

IFigure* Factory::createFigure(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width, FigureType figure_type) {
    return Factory::creators[figure_type].get()->create(points, line_color, fill_color, width);
}

std::unordered_map<FigureType, std::unique_ptr<ICreator>> Factory::creators = {};
