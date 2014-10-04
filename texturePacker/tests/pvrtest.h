#ifndef PVRTEST_H
#define PVRTEST_H

#include "imagetest.h"

class PVRTest : public ImageTest
{
    Q_OBJECT
public:
    PVRTest();

private Q_SLOTS:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    virtual void testLoad();
};

#endif // PVRTEST_H
