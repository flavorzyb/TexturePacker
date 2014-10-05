#include "pvrtest.h"
#include "common/include/pvr.h"

PVRTest::PVRTest()
{
}

void PVRTest::initTestCase()
{
    m_pImg = new PVR("images/zw_bs.pvr");
}

void PVRTest::cleanupTestCase()
{
    delete m_pImg;
}

void PVRTest::testLoad()
{
    QCOMPARE(m_pImg->load("images/zw_bs.pvr.ccz"), true);
    QVERIFY2(m_pImg->width() > 1, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 1, "height must be over then zero.");

    QCOMPARE(m_pImg->load("images/zw_bsaduoj.pvr.ccz"), false);
    QVERIFY2(m_pImg->width() > 1, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 1, "height must be over then zero.");
}
