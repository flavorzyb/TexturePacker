#include "s3tcencodetest.h"
#include "include/s3tcencode.h"

S3TCEncodeTest::S3TCEncodeTest() :
    QObject()
{
}

S3TCEncodeTest::~S3TCEncodeTest()
{
}

void S3TCEncodeTest::init()
{
    m_pngPath = "images/zw_shu_512.png";
}

void S3TCEncodeTest::cleanup()
{
}

void S3TCEncodeTest::testConvert()
{
    S3TCEncode encode;
    S3TC * result = encode.convert(m_pngPath);
    QVERIFY(result != NULL);
    QCOMPARE(result->width(), 512);
    QCOMPARE(result->height(), 512);
}
