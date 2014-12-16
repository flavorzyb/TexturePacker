#include "etcheadertest.h"
#include "common/include/etcheader.h"
#include "common/include/fileutils.h"

ETCHeaderTest::ETCHeaderTest()
{
}

void ETCHeaderTest::init()
{
    m_etcFilePath = "images/zw_shu.pkm";
}

void ETCHeaderTest::cleanup()
{
}

void ETCHeaderTest::testLoadETCHeader()
{
    unsigned long size = 0;
    unsigned char * data = FileUtils::getFileData(m_etcFilePath, "rb", &size);
    QVERIFY(size > 16);
    QVERIFY(data != NULL);

    ETCHeader header(data);
    QVERIFY(header.getWidth() == 500);
    QVERIFY(header.getHeight() == 1000);
}
