#include "etcheadertest.h"
#include "include/etcheader.h"
#include "include/fileutils.h"

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
    unsigned char * data = FileUtils::getFileData(m_etcFilePath.toStdString().c_str(), "rb", &size);
    QVERIFY(size > 16);
    QVERIFY(data != NULL);

    ETCHeader header(data);
    QVERIFY(header.getWidth() == 500);
    QVERIFY(header.getHeight() == 1000);
}
