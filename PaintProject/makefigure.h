#ifndef MAKEFIGURE_H
#define MAKEFIGURE_H

#include <QWidget>
#include "paintscene.h"
#include "figuretype.h"

namespace Ui {
class MakeFigure;
}

class MakeFigure : public QWidget {
    Q_OBJECT

public:
    MakeFigure(PaintScene* scene, QWidget *parent = nullptr);
    QSize sizeHint() const;
    ~MakeFigure();

private slots:
    void on_add_dot_button_clicked();

    void on_figures_list_activated(const QString &arg1);

    void on_x_coord_line_textChanged(const QString &arg1);

    void on_y_coord_line_textChanged(const QString &arg1);

    void on_create_figure_button_clicked();

    void on_reset_button_clicked();

private:
    Ui::MakeFigure *ui;
    PaintScene* scene;
    QPointF current_point;
    FigureType type;
    std::vector<QPointF> points;
};

#endif // MAKEFIGURE_H
