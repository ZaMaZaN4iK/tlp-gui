//#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTranslator translator;
    //translator.load("main_pl.qm","/home/zamazan4ik/tlp-gui/translations");
    //a.installTranslator(&translator);
    MainWindows w;
    w.show();
    return a.exec();
}
