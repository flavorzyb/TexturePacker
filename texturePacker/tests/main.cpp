#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"
#include "pngtest.h"
#include "pvrtest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fileUtils;
    PublisherTest publish;
    PngTest png;
    PVRTest pvr;

//    QTest::qExec(&fileUtils, argc, argv);
//    QTest::qExec(&publish, argc, argv);
    QTest::qExec(&png, argc, argv);
//    QTest::qExec(&pvr, argc, argv);

    return 0;
}
