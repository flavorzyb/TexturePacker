#include "etcencodetest.h"
#include "include/etcencode.h"

ETCEncodeTest::ETCEncodeTest():QObject()
{
}

void ETCEncodeTest::init()
{
    m_pngPath = "images/zw_shu.png";
}

void ETCEncodeTest::cleanup()
{
}

void ETCEncodeTest::testConvert()
{
    ETCEncode encode;
    ETC * etc = encode.convert(m_pngPath);
    QVERIFY(etc != NULL);
    QCOMPARE(etc->width(), 500);
    QCOMPARE(etc->height(), 1000);

    etc->save("output/zw_shu.pkm");
}
