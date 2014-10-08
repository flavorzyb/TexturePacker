#ifndef READERTEST_H
#define READERTEST_H

#include <QTest>
#include <QObject>
#include "common/include/reader.h"

class ReaderTest : public QObject
{
    Q_OBJECT
public:
    ReaderTest();
    enum{HEAD_DATA_SIZE=8};
private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    void testReadAll();
signals:

public slots:

private:
    Reader * m_reader;
};

#endif // READERTEST_H
