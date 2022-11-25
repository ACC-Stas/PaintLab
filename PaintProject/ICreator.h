#ifndef ICREATOR_H
#define ICREATOR_H

#include "ifigure.h"
#include "figuretype.h"

#include <QObject>

class ICreator : public QObject {
protected:
    FigureType figureType;
public:
    virtual IFigure* create(std::vector<QPointF> points, QColor line_color, QColor fill_color, int width) = 0;

    FigureType getFigureType() {
        return this->figureType;
    }
};

Q_DECLARE_INTERFACE(ICreator, "com.mysoft.Application.ICreator")

#endif // ICREATOR_H
