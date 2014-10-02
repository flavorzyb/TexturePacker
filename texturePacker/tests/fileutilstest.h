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
};

#endif // FILEUTILSTEST_H
