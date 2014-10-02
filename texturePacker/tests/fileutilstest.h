#ifndef FILEUTILSTEST_H
#define FILEUTILSTEST_H

#include <QObject>
#include <QTest>
#include <QString>

#include "common/include/fileutils.h"

class FileUtilsTest : public QObject
{
    Q_OBJECT
public:
    FileUtilsTest();

signals:

public slots:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testHasParentDirectory();
    void testCreateParentDirectory();
    void testGetAllImageFiles();
private:
    void init();
    void clean();
private:
    QString m_inputPath;
    QString m_outputPath;
};

#endif // FILEUTILSTEST_H
