#include "png2bipcachetest.h"

Png2BipCacheTest::Png2BipCacheTest()
{

}

void Png2BipCacheTest::init()
{
    m_cache = new Png2BipCache;
}

void Png2BipCacheTest::cleanup()
{
    delete m_cache;
}

void Png2BipCacheTest::testLoad()
{
    QCOMPARE(m_cache->load("images/png2bip.cache"), true);
    QVERIFY(m_cache->size() == 2);
    QCOMPARE(m_cache->load("images/png2bipxx33d.cache"), false);
    QVERIFY(m_cache->size() == 0);
}

void Png2BipCacheTest::testSave()
{
    QCOMPARE(m_cache->save("output/png2bip.cache"), false);

    Png2BipCahceVO vo;
    vo.setPngFilePath("common/aa.png");
    vo.setPngFileMd5String("aaaaaaaa");
    vo.setBipFilePath("common/aa.bip");
    vo.setBipFileMd5String("bbbbbbbb");
    m_cache->add(vo);

    vo.setPngFilePath("common/bb.png");
    vo.setPngFileMd5String("cccccc");
    vo.setBipFilePath("common/bb.bip");
    vo.setBipFileMd5String("ddddddd");
    m_cache->add(vo);

    QCOMPARE(m_cache->save("output/png2bip.cache"), true);
}
