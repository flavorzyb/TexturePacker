#include "pvrtest.h"
#include "common/include/pvr.h"

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
    QCOMPARE(m_pImg->load("images/zw_bs.pvr.ccz"), true);
    QVERIFY2(m_pImg->width() > 1, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 1, "height must be over then zero.");

    QCOMPARE(m_pImg->load("images/zw_bsaduoj.pvr.ccz"), false);
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
    QCOMPARE(((PVR *) m_pImg)->saveCCZ("output/zw.pvr.ccz"), true);
}
