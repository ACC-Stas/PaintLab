#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <factory.h>
#include <QComboBox>
#include <iterator>
#include <string>

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(int *figureType, QComboBox *box, QObject *parent = 0);
    ~paintScene();
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
    QPointF previousPoint;
    bool isSecond;
    std::vector<IFigure*> figures;
    std::vector<IFigure*> tempFigures;
    std::vector<IFigure*> redoFigures;
    QColor lineColor;
    QColor fillColor;
    int width;
    int *figureType;
    QComboBox *box;
    bool copy;
    bool isSelected;
    bool isPolyline;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
