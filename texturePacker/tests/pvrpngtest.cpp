#include "pvrpngtest.h"
#include "common/include/pvrpng.h"

PVRPNGTest::PVRPNGTest()
{
}

void PVRPNGTest::initTestCase()
{
    m_oPVR = new PVRPNG("/Users/flavor/tmp/zw_input/植物_树1.png");
}

void PVRPNGTest::cleanupTestCase()
{
    delete m_oPVR;
}

void PVRPNGTest::testLoad()
{
    printf("PVRPNGTest::testLoad()................\n");
}
