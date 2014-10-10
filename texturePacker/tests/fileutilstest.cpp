#include <QDir>
#include <QVector>
#include "fileutilstest.h"

FileUtilsTest::FileUtilsTest()
{
}

void FileUtilsTest::init()
{
    m_inputPath = "input";
    m_outputPath = "output";
}

void FileUtilsTest::cleanup()
{
    QDir dir(m_outputPath);
    if (dir.exists())
    {
        dir.rmpath(dir.absolutePath());
    }
}

void FileUtilsTest::testHasParentDirectory()
{
    QString path = m_inputPath + "/植物_树1.png";
    QCOMPARE(FileUtils::hasParentDirectory("/asadfxi/32ad0ol/"), false);
    QCOMPARE(FileUtils::hasParentDirectory(path), true);
}

void FileUtilsTest::testCreateParentDirectory()
{
    QString path = m_outputPath + "/aaaa/bbb/植物_树1.png";

    QCOMPARE(FileUtils::createParentDirectory(path), true);
    QCOMPARE(FileUtils::createParentDirectory(path), true);
}

void FileUtilsTest::testGetAllImageFiles()
{
    QVector<QString> fileLists = FileUtils::getAllImageFiles(m_inputPath);
    QVERIFY(fileLists.size() > 0);
}

void FileUtilsTest::testMd5()
{
    //md5===486eb65274adb86441072afa1e2289f3
    QCOMPARE(FileUtils::md5("this is a test string"), tr("486eb65274adb86441072afa1e2289f3"));
    //md5===a516e6a1a26650f2e2a496d24a70964a
    QCOMPARE(FileUtils::md5("this is a title...#$#%%"), tr("a516e6a1a26650f2e2a496d24a70964a"));

    //md5===7f05f90ad80ff20f9f893742edfe1697
    QCOMPARE(FileUtils::md5File("images/zw_bs.png"), tr("7f05f90ad80ff20f9f893742edfe1697"));
    //md5===1d06459577a276e6832c45740341b714
    QCOMPARE(FileUtils::md5File("images/zw_bs.jpg"), tr("1d06459577a276e6832c45740341b714"));
}
