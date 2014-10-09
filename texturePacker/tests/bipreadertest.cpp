#include "bipreadertest.h"


BipReaderTest::BipReaderTest()
{
}

void BipReaderTest::init()
{
    m_reader = new BipReader("images/zw_shu.bip");
}

void BipReaderTest::cleanup()
{
    delete m_reader;
}

void BipReaderTest::testLoad()
{
    PVR * result = m_reader->load();
    QVERIFY(result != NULL);

//    result = m_reader->load("images/zw_shuasdbdc.bip");
//    QVERIFY(result == NULL);
}
