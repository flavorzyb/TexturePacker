#ifndef BIPREADERTEST_H
#define BIPREADERTEST_H

#include <QTest>
#include <QObject>

#include "common/include/bipreader.h"

class BipReaderTest : public QObject
{
    Q_OBJECT
public:
    BipReaderTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    void testLoad();

private:
    BipReader * m_reader;
};

#endif // BIPREADERTEST_H
