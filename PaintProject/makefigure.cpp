#include "makefigure.h"
#include "figuretype.h"
#include "ui_makefigure.h"

MakeFigure::MakeFigure(PaintScene* scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeFigure) {
    ui->setupUi(this);

    for (const FigureType& figure : FigureType::all) {
        ui->figures_list->addItem(QString::fromStdString(figure.getValue()));
    }

    this->scene = scene;
    this->type = FigureType("line");

    ui->x_coord_line->setValidator(new QDoubleValidator(0, 1000, 15, ui->x_coord_line));
    ui->y_coord_line->setValidator(new QDoubleValidator(0, 1000, 15, ui->y_coord_line));
}

MakeFigure::~MakeFigure() {
    delete ui;
}

void MakeFigure::on_add_dot_button_clicked() {
    points.push_back(current_point);
}

QSize MakeFigure::sizeHint() const {
   return QSize(100, 110);
}

void MakeFigure::on_figures_list_activated(const QString &arg1) {
    ui->error_label->clear();
    type = FigureType(arg1.toStdString());
}

void MakeFigure::on_x_coord_line_textChanged(const QString &arg1) {
    ui->error_label->clear();
    current_point.setX(arg1.toDouble());
}

void MakeFigure::on_y_coord_line_textChanged(const QString &arg1) {
    ui->error_label->clear();
    current_point.setY(arg1.toDouble());
}

void MakeFigure::on_create_figure_button_clicked() {
    ui->error_label->clear();
    if (points.size() < 2) {
        ui->error_label->setText("Need 2 or more dots");
        return;
    }

    if (points.size() > 2 && (type != FigureType("polygon") || type != FigureType("polyline"))) {
        ui->error_label->setText("Need 2 dots for this type");
        return;
    }

    scene->figures.push_back(std::unique_ptr<IFigure>(Factory::createFigure(points, scene->getLineColor(), scene->getFillColor(), scene->getWidth(), type)));
    scene->updateScene();
    points.clear();
}

void MakeFigure::on_reset_button_clicked() {
    ui->error_label->clear();
    ui->x_coord_line->clear();
    ui->y_coord_line->clear();
    current_point = QPointF();
    points.clear();
}
