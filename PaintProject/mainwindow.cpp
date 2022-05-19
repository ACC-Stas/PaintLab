#include "mainwindow.h"
#include "makefigure.h"
#include "ui_mainwindow.h"
#include <regex>

#include "figuretype.h"
#include "factory.h"
#include "creators/LineCreator.h"
#include "creators/ellipsecreator.h"
#include "creators/polygoncreator.h"
#include "creators/rectanglecreator.h"

#include <QPluginLoader>
#include <QDir>
#include <iostream>
#include <fstream>

void includePlugins();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    includePlugins();

    figure_type = FigureType("line");
    scene = new PaintScene(&figure_type, ui->comboBox);
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    ui->graphicsView->setScene(scene);

    figure_window = std::unique_ptr<MakeFigure> (new MakeFigure(scene));
    for (const FigureType& type : FigureType::all) {
        ui->figure_types_list->addItem(QString::fromStdString(type.getValue()));
    }

    download("output.txt");
}

MainWindow::~MainWindow() {

    if(selected_figure.size() != 0 ) {

        std::regex number_regex("(\\d+)");
        std::string text = selected_figure.toStdString();
        auto it = std::sregex_token_iterator(text.cbegin(), text.cend(), number_regex, 1);
        int figureNumber = std::stoi(*it) - 1;


        scene->figures.at(figureNumber)->setLineColor(scene->figures.at(figureNumber)->getTempLineColor());
    }

    save();
    delete ui;
    delete scene;
}

void MainWindow::on_actionLine_triggered() {
    figure_type = FigureType("line");
}

void MainWindow::on_actionUndo_triggered() {
    scene->undo();
}

void MainWindow::on_actionRedo_triggered() {
    scene->redo();
}

void MainWindow::on_comboBox_activated(const QString &arg1) {
    scene->setIsSelected(true);
    selected_figure = arg1;
    auto temp = scene->getFigures();

    if(previous_figure.size() != 0 ) {

        std::regex number_regex("(\\d+)");
        std::string text = previous_figure.toStdString();
        auto it = std::sregex_token_iterator(text.cbegin(), text.cend(), number_regex, 1);
        int figureNumber = std::stoi(*it) - 1;


        temp->at(figureNumber)->setLineColor(temp->at(figureNumber)->getTempLineColor());
    }
    previous_figure = selected_figure;


    std::regex number_regex("(\\d+)");
    std::string text = previous_figure.toStdString();
    auto it = std::sregex_token_iterator(text.cbegin(), text.cend(), number_regex, 1);
    int figureNumber = std::stoi(*it) - 1;


    temp->at(figureNumber)->setLineColor(QColor(24,167,181));
    scene->updateScene();
}

void MainWindow::on_pushButton_clicked() {
    if(scene->getIsSelected()){
        scene->deleteFigure(selected_figure, &previous_figure);
    }
}

void MainWindow::on_pushButton_2_clicked() {
    if(scene->getIsSelected()){
        scene->setcopy(true);
    }
}

void MainWindow::on_actionRed_triggered() {
    scene->setLineColor(QColor(255, 0, 0));
}

void MainWindow::on_actionGreen_triggered() {
    scene->setLineColor(QColor(0, 255, 0));
}

void MainWindow::on_actionBlue_triggered() {
    scene->setLineColor(QColor(0, 0, 255));
}

void MainWindow::on_action3_triggered() {
    scene->setWidth(3);
}

void MainWindow::on_action6_triggered() {
    scene->setWidth(6);
}

void MainWindow::on_action9_triggered() {
    scene->setWidth(9);
}

void MainWindow::on_action12_triggered() {
    scene->setWidth(12);
}

void MainWindow::on_actionRed_2_triggered() {
    scene->setFillColor(QColor(255, 0, 0));
}

void MainWindow::on_actionGreen_2_triggered() {
    scene->setFillColor(QColor(0, 255, 0));
}

void MainWindow::on_actionBlue_2_triggered() {
    scene->setFillColor(QColor(0, 0, 255));
}

void MainWindow::on_make_figure_button_clicked() {
    figure_window = std::unique_ptr<MakeFigure>(new MakeFigure(scene));
    figure_window->show();
}

void MainWindow::on_figure_types_list_activated(const QString &arg1) {
    figure_type = FigureType(arg1.toStdString());

    scene->setIsPolyline(false);
    scene->setIsPolygon(false);

    if (figure_type == FigureType("polyline")) {
        scene->setIsPolyline(true);
    }

    if (figure_type == FigureType("polygon")) {
        scene->setIsPolygon(true);

    }
}

void MainWindow::save() {
    std::vector<std::unique_ptr<IFigure>>* figures = this->scene->getFigures();

    std::string output;
    for (size_t i = 0; i < figures->size(); ++i) {
        output.append(figures->at(i).get()->serialize());
    }

    std::ofstream out("output.txt");
    out << output;
    out.close();
}

IFigure* ReadFigure(std::ifstream& fin) {
    std::string line;
    std::getline(fin, line);
    int point_number = std::stoi(line);

    std::vector<QPointF> points;

    for (int i = 0; i < point_number; ++i) {
        std::getline(fin, line);
        float x = std::stof(line);
        std::getline(fin, line);
        float y = std::stof(line);

        points.push_back(QPointF(x, y));
    }

    std::getline(fin, line);
    float r = std::stoi(line);
    std::getline(fin, line);
    float g = std::stoi(line);
    std::getline(fin, line);
    float b = std::stoi(line);

    QColor line_color = QColor(r, g, b);

    std::getline(fin, line);
    r = std::stoi(line);
    std::getline(fin, line);
    g = std::stoi(line);
    std::getline(fin, line);
    b = std::stoi(line);

    QColor fill_color = QColor(r, g, b);

    std::getline(fin, line);
    int width = std::stoi(line);

    std::getline(fin, line);
    FigureType type(line);
    return Factory::createFigure(points, line_color, fill_color, width, type);
}

void MainWindow::download(std::string filename) {
    std::ifstream fin(filename);

    std::string line;
    while (fin.peek() != EOF) {
        scene->figures.push_back(std::unique_ptr<IFigure>(ReadFigure(fin)));
        scene->box->addItem(QString("figure" + QString::number(scene->figures.size())));
        scene->updateScene();
    }
}

void includePlugins() {
    Factory::creators[FigureType("line")] = std::unique_ptr<LineCreator>(new LineCreator());
    FigureType::all.insert("line");
    Factory::creators[FigureType("polyline")] = std::unique_ptr<LineCreator>(new LineCreator());
    FigureType::all.insert("polyline");
    Factory::creators[FigureType("rectangle")] = std::unique_ptr<RectangleCreator>(new RectangleCreator());
    FigureType::all.insert("rectangle");
    Factory::creators[FigureType("ellipse")] = std::unique_ptr<EllipseCreator>(new EllipseCreator());
    FigureType::all.insert("ellipse");
    Factory::creators[FigureType("polygon")] = std::unique_ptr<PolygonCreator>(new PolygonCreator());
    FigureType::all.insert("polygon");

    // загрузить плагин из директории plugins

    QStringList listFiles;
    QDir dir(QApplication::applicationDirPath() + "/plugins/");
            // Поиск всех файлов в папке "Plugins"if(dir.exists())
    listFiles = dir.entryList(QStringList("*"), QDir::Files);
            // Проход по всем файлам
    for(QString str: listFiles) {
        QPluginLoader loader(dir.absolutePath() + "/" +str);
        QObject *pobj = 0;
              // Загрузка плагина
        pobj = qobject_cast<QObject*>(loader.instance());
        if(!pobj) {
            continue;
        }
        ICreator *pluginObject;
        pluginObject = 0;
              // Получения интерфейсов
        pluginObject = qobject_cast<ICreator *>(pobj);

        Factory::creators[pluginObject->getFigureType()] = std::unique_ptr<ICreator>(pluginObject);
        FigureType::all.insert(pluginObject->getFigureType().getValue());
    }
}
