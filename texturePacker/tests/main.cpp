#include <QTest>
#include "fileutilstest.h"
#include "publishertest.h"

int main(int argc, char *argv[])
{
    FileUtilsTest fut;
    PublisherTest pt;

    QTest::qExec(&fut, argc, argv);
    QTest::qExec(&pt, argc, argv);

    return 0;
}
