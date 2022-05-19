#ifndef FACTORY_H
#define FACTORY_H

#pragma once
#include <memory>
#include "ifigure.h"
#include "unordered_map"
#include "figuretype.h"
#include "ICreator.h"

class Factory {
public:
    static IFigure* createFigure(std::vector<QPointF> points, QColor lineColor, QColor fillColor, int width, FigureType figureType);
    static std::unordered_map<FigureType, std::unique_ptr<ICreator>> creators;
};

#endif // FACTORY_H
