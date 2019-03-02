#include "mainwindow.h"
#include <QApplication>
#include <com_rand.h>
std::mt19937 Generator::mt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
