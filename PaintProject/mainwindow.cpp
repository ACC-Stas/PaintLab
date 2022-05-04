#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    figureType = 1;
    scene = new paintScene(&figureType, ui->comboBox);
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
}

void MainWindow::on_actionLine_triggered() {
    figureType = 1;
}

void MainWindow::on_actionUndo_triggered() {
    scene->undo();
}

void MainWindow::on_actionRedo_triggered() {
    scene->redo();
}

void MainWindow::on_comboBox_activated(const QString &arg1) {
    scene->setIsSelected(true);
    selectedFigure = arg1;
    auto temp = scene->getFigures();

    if(prevFigure.size() != 0 ) {
        temp->at(prevFigure.toStdString().back() - '0' - 1)->setLineColor(temp->at(prevFigure.toStdString().back() - '0' - 1)->getTempLineColor());
    }
    prevFigure = selectedFigure;
    temp->at((selectedFigure.toStdString().back() - '0') - 1)->setLineColor(QColor(24,167,181));
    scene->updateScene();
}

void MainWindow::on_pushButton_clicked() {
    if(scene->getIsSelected()){
        scene->deleteFigure(selectedFigure, &prevFigure);
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

void MainWindow::on_actionEllipse_triggered() {
    figureType = 3;
}

void MainWindow::on_actionRectangle_triggered() {
    figureType = 2;
}

void MainWindow::on_actionPolygon_triggered() {
    figureType = 4;
}

void MainWindow::on_actionPolyline_triggered() {
    scene->setIsPolyline(true);
    figureType = 1;
}
