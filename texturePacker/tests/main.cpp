#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"
#include "pngtest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fut;
    PublisherTest pt;
    PngTest pngTest;

    QTest::qExec(&fut, argc, argv);
    QTest::qExec(&pt, argc, argv);
    QTest::qExec(&pngTest, argc, argv);

    return 0;
}
