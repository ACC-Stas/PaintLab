#include "makefigure.h"
#include "ui_makefigure.h"

MakeFigure::MakeFigure(PaintScene* scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeFigure) {
    ui->setupUi(this);

    ui->figures_list->addItem("ABOBA");
    this->scene = scene;
}

MakeFigure::~MakeFigure() {
    delete ui;
}

void MakeFigure::on_add_dot_button_clicked() {
    ui->error_label->setText(QString::fromStdString(std::to_string(scene->getWidth())));
}

QSize MakeFigure::sizeHint() const {
   return QSize(100, 110);
}

void MakeFigure::on_figures_list_activated(const QString &arg1) {
    ui->error_label->setText(arg1);
}

void MakeFigure::on_x_coord_line_textChanged(const QString &arg1) {
    ui->error_label->setText(arg1);
}

void MakeFigure::on_y_coord_line_textChanged(const QString &arg1) {

}

void MakeFigure::on_create_figure_button_clicked() {

}

void MakeFigure::on_reset_button_clicked() {
    ui->error_label->clear();
    ui->x_coord_line->clear();
    ui->y_coord_line->clear();
}
