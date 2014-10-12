#ifndef PVRTEST_H
#define PVRTEST_H

#include "imagetest.h"
#include "common/include/pvr.h"

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
    void testConvertToPng();
protected:
    virtual Image * getImage();
private:
    PVR * m_pImg;
};

#endif // PVRTEST_H
