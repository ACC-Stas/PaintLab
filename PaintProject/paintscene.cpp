#include "paintscene.h"

paintScene::paintScene(int *figureType, QComboBox *box, QObject *parent) : QGraphicsScene(parent) {
    lineColor.setRgb(0, 0, 0);
    fillColor.setRgb(1, 1, 1);
    width = 3;
    isSecond = false;
    this->figureType = figureType;
    this->box = box;
    copy = false;
    isSelected = false;
    isPolyline = false;
}

paintScene::~paintScene() {
}

void paintScene::updateScene() {
    clear();
    for(unsigned long i = 0; i < figures.size(); i++) {
        addItem(figures[i]->draw());
    }
    for(unsigned long i = 0; i < tempFigures.size(); i++) {
        addItem(tempFigures[i]->draw());
    }
}

bool paintScene::getcopy() const {
    return copy;
}

void paintScene::setcopy(bool value) {
    copy = value;
}

bool paintScene::getIsSelected() const {
    return isSelected;
}

void paintScene::setIsSelected(bool value) {
    isSelected = value;
}

QColor paintScene::getLineColor() const {
    return lineColor;
}

void paintScene::setLineColor(const QColor &value) {
    lineColor = value;
}

QColor paintScene::getFillColor() const {
    return fillColor;
}

void paintScene::setFillColor(const QColor &value) {
    fillColor = value;
}

bool paintScene::getIsPolyline() const
{
    return isPolyline;
}

void paintScene::setIsPolyline(bool value)
{
    isPolyline = value;
}

void paintScene::undo() {
    if(!figures.empty()){
        redoFigures.push_back(std::move(figures.back()));
        figures.pop_back();
        box->removeItem(figures.size());
        updateScene();
    }
}

void paintScene::redo() {
    if(!redoFigures.empty()){
        figures.push_back(std::move(redoFigures.back()));
        redoFigures.pop_back();
        updateScene();
        box->addItem(QString("figure" + QString::number(figures.size())));
    }
}

void paintScene::deleteFigure(QString figureName, QString *prevFigure) {
    auto iter = figures.begin();
    int i;
    for(i = 0; i < (figureName.toStdString().back() - '0') - 1; i++){
        iter++;
    }
    (*iter)->setLineColor((*iter)->getTempLineColor());
    redoFigures.push_back(std::move(*iter));
    figures.erase(iter);
    updateScene();
    box->removeItem(box->count() - 1);
    *prevFigure = "";
    isSelected = false;
}

std::vector<IFigure*>* paintScene::getFigures() {
    return &figures;
}


int paintScene::getWidth() const {
    return width;
}

void paintScene::setWidth(int value) {
    width = value;
}


void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(isPolyline) {
        if (event->button() == Qt::LeftButton && !isSecond){
            previousPoint = event->scenePos();
            isSecond = true;
            return;
        }

        if (event->button() == Qt::LeftButton && isSecond){
            previousPoint = event->scenePos();
            figures.push_back(std::move(tempFigures.back()));
            tempFigures.clear();

            box->addItem(QString("figure" + QString::number(figures.size())));
            updateScene();
            copy = false;

            if(!redoFigures.empty()) {
                redoFigures.clear();
            }

            return;
        }

        if (event->button() == Qt::RightButton && isSecond){
            tempFigures.clear();
            updateScene();
            isSecond = false;
            copy = false;

            return;
        }
        return;
    }

    if (event->button() == Qt::LeftButton && (isSecond || copy)){
        figures.push_back(std::move(tempFigures.back()));
        tempFigures.clear();
        box->addItem(QString("figure" + QString::number(figures.size())));
        updateScene();

        isSecond = false;
        copy = false;

        if(!redoFigures.empty()){
            redoFigures.clear();
        }

        return;
    }

    if (event->button() == Qt::RightButton && (isSecond || copy)){
        tempFigures.clear();
        updateScene();
        isSecond = false;
        copy = false;

        return;
    }

    if (event->button() == Qt::LeftButton && !isSecond){
        previousPoint = event->scenePos();
        isSecond = true;
        return;
    }

}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    tempFigures.clear();
    if(isSecond) {
        tempFigures.push_back(factory::createFigure(previousPoint, event->scenePos(), lineColor, fillColor, width, *figureType));
        updateScene();
    }
    if(copy) {
        int figureNumber = box->currentText().toStdString().back() - '0' - 1;
        auto width = figures.at(figureNumber)->getPoint2().x() - figures.at(figureNumber)->getPoint1().x();
        auto height = figures.at(figureNumber)->getPoint2().y() - figures.at(figureNumber)->getPoint1().y();
        QPointF point(event->scenePos().x() + width, event->scenePos().y() + height);
        tempFigures.push_back(factory::createFigure(event->scenePos(), point, figures.at(figureNumber)->getTempLineColor(), figures.at(figureNumber)->getFillColor(), figures.at(figureNumber)->getWidth(), figures.at(figureNumber)->getFigureType()));
        updateScene();
    }
}
