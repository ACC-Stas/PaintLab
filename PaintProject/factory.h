#ifndef FACTORY_H
#define FACTORY_H

#pragma once
#include <memory>
#include <line.h>
#include <rectangle.h>
#include <ellipse.h>
#include <polygon.h>

class factory {
public:
    static IFigure* createFigure(QPointF point1, QPointF point2, QColor lineColor, QColor fillColor, int width, int figureType);
};

#endif // FACTORY_H
