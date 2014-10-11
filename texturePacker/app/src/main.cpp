#include <QApplication>
#include "include/mainwindow.h"
#include "common/include/fileutils.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    for(int i = 0; i<argc; i++)
//    {
//        printf("argv[%d]=%s\n", i, argv[i]);
//        FileUtils::writeFile("/Users/flavor/tmp/tp.dat", "ab+", argv[i], strlen(argv[i]));
//    }

    MainWindow w;
    w.show();
    return a.exec();
}
