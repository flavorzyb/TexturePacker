#include "pngtest.h"
#include "common/include/png.h"
#include "common/include/pvr.h"

PngTest::PngTest()
{
}

void PngTest::init()
{
    m_image = new PNG("input/植物_树1.png");
}

void PngTest::cleanup()
{
    delete m_image;
}

void PngTest::testLoad()
{
    QCOMPARE(m_image->load(), true);
    QCOMPARE(m_image->loadFile("input/植物_树1xxaiejl.png"), false);
}

void PngTest::testSave()
{
    QCOMPARE(m_image->save("output/zw_test.png"), false);
    m_image->load();
    QCOMPARE(m_image->save("output/zw_test.png"), true);
}

void PngTest::testConvertToPVR()
{
    m_image->load();
    PVR * result = m_image->convertToPVR();
    QVERIFY(result != NULL);
    QCOMPARE(result->save("output/zw_shu.pvr"), true);
    QCOMPARE(result->saveCCZ("output/zw_shu.pvr.ccz"), true);

    delete result;
}

Image *PngTest::getImage()
{
    return m_image;
}
