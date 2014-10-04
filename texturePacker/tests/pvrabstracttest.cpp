#include "pvrabstracttest.h"

PVRAbstractTest::PVRAbstractTest()
{
}

PVRAbstractTest::~PVRAbstractTest()
{

}

void PVRAbstractTest::testWidth()
{
    QVERIFY2(m_oPVR->width() > 0, "width must be over then zero.");
}

void PVRAbstractTest::testHeight()
{
    QVERIFY2(m_oPVR->height() > 0, "height must be over then zero.");
}
