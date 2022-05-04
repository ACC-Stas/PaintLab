#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <factory.h>
#include <QComboBox>
#include <iterator>
#include <string>

class PaintScene : public QGraphicsScene {

    Q_OBJECT

public:
    explicit PaintScene(FigureType *figure_type, QComboBox *box, QObject *parent = 0);
    ~PaintScene();
    void undo();
    void redo();
    void deleteFigure(QString figureName, QString* prevFigure);

    std::vector<IFigure*>* getFigures();

    int getWidth() const;
    void setWidth(int value);
    void updateScene();

    bool getcopy() const;
    void setcopy(bool value);

    bool getIsSelected() const;
    void setIsSelected(bool value);

    QColor getLineColor() const;
    void setLineColor(const QColor &value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    bool getIsPolyline() const;
    void setIsPolyline(bool value);

private:
    QPointF previous_point;
    bool isSecond;
    std::vector<IFigure*> figures;
    std::vector<IFigure*> temp_figures;
    std::vector<IFigure*> redo_figures;
    QColor line_color;
    QColor fill_color;
    int width;
    FigureType *figure_type;
    QComboBox *box;
    bool copy;
    bool is_selected;
    bool is_polyline;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    friend class MakeFigure;
};

#endif // PAINTSCENE_H
