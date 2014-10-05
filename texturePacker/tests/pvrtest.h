#ifndef PVRTEST_H
#define PVRTEST_H

#include "imagetest.h"

class PVRTest : public ImageTest
{
    Q_OBJECT
public:
    PVRTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    virtual void testLoad();
    void testSave();
    void testSaveCCZFile();
};

#endif // PVRTEST_H
