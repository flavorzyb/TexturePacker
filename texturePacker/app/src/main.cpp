#include "include/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cd("plugins");
    QApplication::setLibraryPaths(QStringList(dir.absolutePath()));

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
