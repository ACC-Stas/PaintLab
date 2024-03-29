#include "paintscene.h"
#include <regex>

PaintScene::PaintScene(FigureType *figureType, QComboBox *box, QObject *parent) : QGraphicsScene(parent) {
    line_color.setRgb(0, 0, 0);
    fill_color.setRgb(1, 1, 1);
    width = 3;
    isSecond = false;
    this->figure_type = figureType;
    this->box = box;
    copy = false;
    is_selected = false;
    is_polyline = false;

    is_polygon = false;
    points_ = std::vector<QPointF>();
}

PaintScene::~PaintScene() {
}

void PaintScene::updateScene() {
    clear();
    for(unsigned long i = 0; i < figures.size(); i++) {
        addItem(figures[i]->draw());
    }
    for(unsigned long i = 0; i < temp_figures.size(); i++) {
        addItem(temp_figures[i]->draw());
    }
}

bool PaintScene::getcopy() const {
    return copy;
}

void PaintScene::setcopy(bool value) {
    copy = value;
}

bool PaintScene::getIsSelected() const {
    return is_selected;
}

void PaintScene::setIsSelected(bool value) {
    is_selected = value;
}

QColor PaintScene::getLineColor() const {
    return line_color;
}

void PaintScene::setLineColor(const QColor &value) {
    line_color = value;
}

QColor PaintScene::getFillColor() const {
    return fill_color;
}

void PaintScene::setFillColor(const QColor &value) {
    fill_color = value;
}

bool PaintScene::getIsPolyline() const {
    return is_polyline;
}

void PaintScene::setIsPolyline(bool value) {
    is_polyline = value;
}

bool PaintScene::getIs_polygon() const {
    return is_polygon;
}

void PaintScene::setIsPolygon(bool value) {
    is_polygon = value;
}

void PaintScene::undo() {
    if(!figures.empty()){
        redo_figures.push_back(std::move(figures.back()));
        figures.pop_back();
        box->removeItem(figures.size());
        updateScene();
    }
}

void PaintScene::redo() {
    if(!redo_figures.empty()){
        figures.push_back(std::move(redo_figures.back()));
        redo_figures.pop_back();
        updateScene();
        box->addItem(QString("figure " + QString::number(figures.size())));
    }
}

void PaintScene::deleteFigure(QString figureName, QString *prevFigure) {
    auto iter = figures.begin();

    std::regex number_regex("(\\d+)");
    std::string text = figureName.toStdString();
    auto it = std::sregex_token_iterator(text.cbegin(), text.cend(), number_regex, 1);
    int figureNumber = std::stoi(*it) - 1;

    for(int i = 0; i < figureNumber; i++){
        iter++;
    }

    (*iter)->setLineColor((*iter)->getTempLineColor());
    redo_figures.push_back(std::move(*iter));
    figures.erase(iter);
    updateScene();
    box->removeItem(box->count() - 1);
    *prevFigure = "";
    is_selected = false;
}

std::vector<std::unique_ptr<IFigure>>* PaintScene::getFigures() {
    return &figures;
}


int PaintScene::getWidth() const {
    return width;
}

void PaintScene::setWidth(int value) {
    width = value;
}


void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(is_polyline) {
        if (event->button() == Qt::LeftButton && !isSecond){
            previous_point = event->scenePos();
            isSecond = true;
            return;
        }

        if (event->button() == Qt::LeftButton && isSecond){
            previous_point = event->scenePos();
            figures.push_back(std::move(temp_figures.back()));
            temp_figures.clear();

            box->addItem(QString("figure" + QString::number(figures.size())));
            updateScene();
            copy = false;

            if(!redo_figures.empty()) {
                redo_figures.clear();
            }

            return;
        }

        if (event->button() == Qt::RightButton && isSecond){
            temp_figures.clear();
            updateScene();
            isSecond = false;
            copy = false;

            return;
        }
        return;
    }

    if (is_polygon) {
        if (event->button() == Qt::LeftButton) {
            points_.push_back(event->scenePos());
            return;
        }

        if (event->button() == Qt::RightButton) {
            figures.push_back(std::move(temp_figures.back()));
            temp_figures.clear();
            points_.clear();

            box->addItem(QString("figure" + QString::number(figures.size())));
            updateScene();
            copy = false;

            if (!redo_figures.empty()) {
                redo_figures.clear();
            }

            return;
        }

        if (event->button() == Qt::RightButton && isSecond){
            temp_figures.clear();
            updateScene();
            isSecond = false;
            copy = false;

            return;
        }

        return;
    }

    if (event->button() == Qt::LeftButton && (isSecond || copy)){
        figures.push_back(std::move(temp_figures.back()));
        temp_figures.clear();
        box->addItem(QString("figure" + QString::number(figures.size())));
        updateScene();

        isSecond = false;
        copy = false;

        if(!redo_figures.empty()){
            redo_figures.clear();
        }

        return;
    }

    if (event->button() == Qt::RightButton && (isSecond || copy)){
        temp_figures.clear();
        updateScene();
        isSecond = false;
        copy = false;

        return;
    }

    if (event->button() == Qt::LeftButton && !isSecond){
        previous_point = event->scenePos();
        isSecond = true;
        return;
    }

}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    temp_figures.clear();

    if(copy) {
        std::regex number_regex("(\\d+)");
        std::string text = box->currentText().toStdString();
        auto it = std::sregex_token_iterator(text.cbegin(), text.cend(), number_regex, 1);
        int figureNumber = std::stoi(*it) - 1;

        auto points = figures.at(figureNumber)->points;
        auto end_point = points.back();

        auto x_shift = end_point.x() - event->scenePos().x();
        auto y_shift = end_point.y() - event->scenePos().y();

        for (auto& point : points) {
            point.setX(point.x() - x_shift);
            point.setY(point.y() - y_shift);
        }

        temp_figures.push_back(std::unique_ptr<IFigure>(Factory::createFigure(points, figures.at(figureNumber)->getTempLineColor(),
                                                     figures.at(figureNumber)->getFillColor(), figures.at(figureNumber)->getWidth(), figures.at(figureNumber)->getFigureType())));
        updateScene();
        return;
    }

    if(isSecond) {
        temp_figures.push_back(std::unique_ptr<IFigure>(Factory::createFigure({previous_point, event->scenePos()}, line_color, fill_color, width, *figure_type)));
        updateScene();
    }

    if (is_polygon && points_.size() > 1) {
        auto temp_points = points_;
        temp_points.push_back(event->scenePos());
        temp_figures.push_back(std::unique_ptr<IFigure>(Factory::createFigure(temp_points, line_color, fill_color, width, *figure_type)));
        updateScene();
    }
}
