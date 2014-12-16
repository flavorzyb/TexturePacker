#include "etctest.h"
#include "include/etc.h"
#include "include/fileutils.h"

ETCTest::ETCTest() :
    QObject()
{
}

void ETCTest::init()
{
    m_etcFilePath = "images/zw_shu.pkm";
    m_etcCCZFilePath = "images/zw_shu.pkm.ccz";

    m_outFilePath = "output/zw_shu_ot.pkm";
    m_outCCZFilePath = "output/zw_shu_ot.pkm.ccz";
}

void ETCTest::cleanup()
{
}

void ETCTest::testLoadFile()
{
    ETC etc(m_etcFilePath);
    QCOMPARE(etc.load(), true);
    QVERIFY(etc.getData() != NULL);
    QVERIFY(etc.getSize() > 16);
    QCOMPARE(etc.width(), 500);
    QCOMPARE(etc.height(), 1000);
}

void ETCTest::testLoadData()
{
    ETC etc;
    unsigned long size = 0;
    unsigned char * data = FileUtils::getFileData(m_etcFilePath, "rb", &size);

    QCOMPARE(etc.loadData(data, size), true);
    QVERIFY(etc.getData() != NULL);
    QVERIFY(etc.getSize() > 16);
    QCOMPARE(etc.width(), 500);
    QCOMPARE(etc.height(), 1000);

    // test load ccz data
    ETC cczETC;
    size = 0;
    data = FileUtils::getFileData(m_etcCCZFilePath, "rb", &size);
    QCOMPARE(cczETC.loadCCZData(data, size), true);
    QVERIFY(cczETC.getData() != NULL);
    QVERIFY(cczETC.getSize() > 16);
    QCOMPARE(cczETC.width(), 500);
    QCOMPARE(cczETC.height(), 1000);
}

void ETCTest::testSave()
{
    ETC etc(m_etcFilePath);
    QCOMPARE(etc.load(), true);
    QCOMPARE(etc.save(m_outFilePath), true);
    QCOMPARE(etc.saveCCZ(m_outCCZFilePath), true);
    unsigned long size = 0;
    unsigned char * out = etc.saveCCZToBuffer(&size);
    QVERIFY(out != NULL);
    QVERIFY(size > 1);
}
