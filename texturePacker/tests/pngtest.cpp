#include "pngtest.h"
#include "common/include/png.h"

PngTest::PngTest()
{
}

void PngTest::init()
{
    m_pImg = new PNG("input/植物_树1.png");
}

void PngTest::cleanup()
{
    delete m_pImg;
}

void PngTest::testLoad()
{
    QCOMPARE(m_pImg->load(), true);
    QCOMPARE(m_pImg->load("input/植物_树1xxaiejl.png"), false);
}

void PngTest::testSave()
{
    QCOMPARE(m_pImg->save("output/zw_test.png"), false);
    m_pImg->load();
    QCOMPARE(m_pImg->save("output/zw_test.png"), true);
}
