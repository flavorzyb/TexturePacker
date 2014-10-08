#ifndef PNGTEST_H
#define PNGTEST_H

#include "imagetest.h"
#include "common/include/png.h"

class PngTest : public ImageTest
{
    Q_OBJECT
public:
    PngTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    virtual void testLoad();
    virtual void testSave();
    void testConvertToPVR();

protected:
    virtual Image * getImage();

private:
    PNG * m_image;
};

#endif // PNGTEST_H
