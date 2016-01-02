//#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindows w;
    w.show();
    return a.exec();
}
