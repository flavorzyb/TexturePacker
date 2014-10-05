#include "imagetest.h"

ImageTest::ImageTest()
{
}

void ImageTest::testWidthAndHeight()
{
    m_pImg->load();
    QVERIFY2(m_pImg->width() > 1, "width must be over then zero.");
    QVERIFY2(m_pImg->height() > 1, "height must be over then zero.");
}
