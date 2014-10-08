#include "imagetest.h"

ImageTest::ImageTest()
{
}

void ImageTest::testWidthAndHeight()
{
    getImage()->load();
    QVERIFY2(getImage()->width() > 1, "width must be over then zero.");
    QVERIFY2(getImage()->height() > 1, "height must be over then zero.");
}
