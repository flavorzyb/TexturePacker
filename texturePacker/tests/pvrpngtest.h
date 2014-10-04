#ifndef PVRPNGTEST_H
#define PVRPNGTEST_H

#include "pvrabstracttest.h"

class PVRPNGTest : public PVRAbstractTest
{
    Q_OBJECT
public:
    PVRPNGTest();

private Q_SLOTS:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    void testLoad();
signals:

public slots:

};

#endif // PVRPNGTEST_H
