#ifndef PNGTEST_H
#define PNGTEST_H

#include "imagetest.h"

class PngTest : public ImageTest
{
public:
    PngTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    virtual void testLoad();
};

#endif // PNGTEST_H
