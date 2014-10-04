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
//    QCOMPARE(m_pImg->load("images/zw_bs.pvr.ccz"), true);
//    QCOMPARE(m_pImg->load("images/zw_bsaduoj.pvr.ccz"), false);
}
