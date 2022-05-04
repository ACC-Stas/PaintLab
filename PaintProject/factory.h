#ifndef FACTORY_H
#define FACTORY_H

#pragma once
#include <memory>
#include "ifigure.h"
#include "unordered_map"
#include "figuretype.h"

class Factory {
public:
    static IFigure* createFigure(std::vector<QPointF> points, QColor lineColor, QColor fillColor, int width, FigureType figureType);

};

#endif // FACTORY_H
