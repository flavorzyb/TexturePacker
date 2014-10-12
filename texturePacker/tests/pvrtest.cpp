#include "pvrtest.h"
#include "common/include/pvr.h"
#include "common/include/png.h"

PVRTest::PVRTest()
{
}

void PVRTest::init()
{
    m_pImg = new PVR("images/zw_bs.pvr");
}

void PVRTest::cleanup()
{
    delete m_pImg;
}

void PVRTest::testLoad()
{
    QCOMPARE(m_pImg->loadFile("images/zw_bs.pvr.ccz"), true);
    QVERIFY2(m_pImg->width() > 1, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 1, "height must be over then zero.");

    QCOMPARE(m_pImg->loadFile("images/zw_bsaduoj.pvr.ccz"), false);
    QCOMPARE(m_pImg->width() > 1, false);
    QCOMPARE(m_pImg->height() > 1, false);
}

void PVRTest::testSave()
{
    m_pImg->load();
    QCOMPARE(m_pImg->save("output/zw.pvr"), true);
}

void PVRTest::testSaveCCZFile()
{
    m_pImg->load();
    QCOMPARE(m_pImg->saveCCZ("output/zw.pvr.ccz"), true);
}

void PVRTest::testConvertToPng()
{
    m_pImg->load();
    PNG * png = m_pImg->convertToPng();
    QVERIFY(png != NULL);
    QCOMPARE(png->save("output/pvr_to_png.png"), true);
}

Image *PVRTest::getImage()
{
    return m_pImg;
}
