#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"
#include "pngtest.h"
#include "pvrtest.h"
#include "readertest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fileUtils;
    PublisherTest publish;
    PngTest png;
    PVRTest pvr;
    Reader reader;

//    QTest::qExec(&fileUtils, argc, argv);
//    QTest::qExec(&publish, argc, argv);
//    QTest::qExec(&png, argc, argv);
//    QTest::qExec(&pvr, argc, argv);
    QTest::qExec(&reader, argc, argv);

    return 0;
}
