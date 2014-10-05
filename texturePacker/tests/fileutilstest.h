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
    void init();
    void cleanup();
    void testHasParentDirectory();
    void testCreateParentDirectory();
    void testGetAllImageFiles();

private:
    QString m_inputPath;
    QString m_outputPath;
};

#endif // FILEUTILSTEST_H
