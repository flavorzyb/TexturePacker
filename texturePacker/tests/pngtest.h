#ifndef PNGTEST_H
#define PNGTEST_H

#include "imagetest.h"

class PngTest : public ImageTest
{
public:
    PngTest();

private Q_SLOTS:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    virtual void testLoad();
};

#endif // PNGTEST_H