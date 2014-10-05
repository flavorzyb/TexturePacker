#ifndef PNGTEST_H
#define PNGTEST_H

#include "imagetest.h"

class PngTest : public ImageTest
{
    Q_OBJECT
public:
    PngTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    virtual void testLoad();
    void testSave();
};

#endif // PNGTEST_H
