#include "mainwindow.h"
#include "ifigure.h"
#include "vector"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
