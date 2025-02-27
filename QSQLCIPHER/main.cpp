#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

    MainWindow w;
    w.show();
    return a.exec();
}
