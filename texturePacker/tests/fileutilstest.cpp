#include <QDir>
#include "fileutilstest.h"

FileUtilsTest::FileUtilsTest()
{
}

void FileUtilsTest::init()
{
    m_inputPath = "/Users/flavor/tmp/zw_input";
    m_outputPath = "/Users/flavor/tmp/zw_output";
}

void FileUtilsTest::clean()
{
    QDir dir(m_outputPath);
    if (dir.exists())
    {
        dir.rmpath(dir.absolutePath());
    }
}

void FileUtilsTest::initTestCase()
{
    init();
}

void FileUtilsTest::cleanupTestCase()
{
    clean();
}

void FileUtilsTest::testHasParentDirectory()
{
    QString path = m_inputPath + "/植物_树1.png";
    QCOMPARE(FileUtils::hasParentDirectory("/asadfxi/32ad0ol/"), false);
    QCOMPARE(FileUtils::hasParentDirectory(path.toStdString()), true);
}

void FileUtilsTest::testCreateParentDirectory()
{
    QString path = m_outputPath + "/aaaa/bbb/植物_树1.png";
    QCOMPARE(FileUtils::createParentDirectory(path.toStdString()), true);
    QCOMPARE(FileUtils::createParentDirectory(path.toStdString()), true);
}

void FileUtilsTest::testGetAllImageFiles()
{
}

QTEST_MAIN(FileUtilsTest)
