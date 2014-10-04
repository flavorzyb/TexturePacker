#include "pvrabstracttest.h"

PVRAbstractTest::PVRAbstractTest()
{
}

PVRAbstractTest::~PVRAbstractTest()
{

}

void PVRAbstractTest::testWidthAndHeight()
{
    m_oPVR->load();
    QVERIFY2(m_oPVR->width() > 0, "width must be over then zero.");
    QVERIFY2(m_oPVR->height() > 0, "height must be over then zero.");
}
