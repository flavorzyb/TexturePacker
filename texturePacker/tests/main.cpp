#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"
#include "pngtest.h"
#include "pvrtest.h"
#include "readertest.h"
#include "writertest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fileUtils;
    PublisherTest publish;
    PngTest png;
    PVRTest pvr;
    ReaderTest reader;
    WriterTest writer;

//    QTest::qExec(&fileUtils, argc, argv);
//    QTest::qExec(&publish, argc, argv);
//    QTest::qExec(&png, argc, argv);
//    QTest::qExec(&pvr, argc, argv);
    QTest::qExec(&reader, argc, argv);
    QTest::qExec(&writer, argc, argv);

    return 0;
}
