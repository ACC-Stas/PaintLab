#ifndef TRAPEZOIDPLUGIN_H
#define TRAPEZOIDPLUGIN_H

#include "TrapezoidPlugin_global.h"
#include "trapezoid.h"
#include "../PaintProject/ICreator.h"

class TRAPEZOIDPLUGIN_EXPORT TrapezoidPlugin : public ICreator {
    Q_OBJECT
    Q_INTERFACES(ICreator)
    Q_PLUGIN_METADATA(IID "com.mysoft.Application.ICreator" FILE "ICreator.json")

public:
    TrapezoidPlugin();
    IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) override {
        return new Trapezoid(points, line_color, fill_color, width);
    }
};

#endif // TRAPEZOIDPLUGIN_H
