#include "imagetest.h"

ImageTest::ImageTest()
{
}

void ImageTest::testWidthAndHeight()
{
    m_pImg->load();
    QVERIFY2(m_pImg->width() > 0, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 0, "height must be over then zero.");
}
