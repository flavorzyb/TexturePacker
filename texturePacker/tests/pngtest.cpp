#include "pngtest.h"
#include "common/include/png.h"

PngTest::PngTest()
{
}

void PngTest::initTestCase()
{
    m_pImg = new PNG("/Users/flavor/tmp/zw_input/植物_树1.png");
}

void PngTest::cleanupTestCase()
{
    delete m_pImg;
}

void PngTest::testLoad()
{
    QCOMPARE(m_pImg->load(), true);
    QCOMPARE(m_pImg->load("/Users/flavor/tmp/zw_input/植物_树1xxaiejl.png"), false);
}
