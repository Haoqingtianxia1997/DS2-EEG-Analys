#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);  //Adaptive monitor resolution
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
