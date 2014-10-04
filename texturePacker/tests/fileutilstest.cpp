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
