#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //setup stylesheet
    QFile file("B:/project/QT/p3/back/Obit.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QString(file.readAll()) };
    a.setStyleSheet(styleSheet);




    w.show();
    return a.exec();
}
