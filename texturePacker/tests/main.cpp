#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"
#include "pvrpngtest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fut;
    PublisherTest pt;
    PVRPNGTest ppt;

    QTest::qExec(&fut, argc, argv);
    QTest::qExec(&pt, argc, argv);
    QTest::qExec(&ppt, argc, argv);

    return 0;
}
