#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ifigure.h"
#include <QGraphicsView>
#include <paintscene.h>
#include <makefigure.h>
#include "figuretype.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_actionLine_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionRed_triggered();

    void on_actionGreen_triggered();

    void on_actionBlue_triggered();

    void on_action3_triggered();

    void on_action6_triggered();

    void on_action9_triggered();

    void on_action12_triggered();

    void on_actionRed_2_triggered();

    void on_actionGreen_2_triggered();

    void on_actionBlue_2_triggered();

    void on_make_figure_button_clicked();

    void on_figure_types_list_activated(const QString &arg1);

private:
    void save();
    void download(std::string filename);

    Ui::MainWindow *ui;
    std::unique_ptr<MakeFigure> figure_window;
    PaintScene *scene;
    FigureType figure_type;
    QString selected_figure;
    QString previous_figure;
};
#endif // MAINWINDOW_H
