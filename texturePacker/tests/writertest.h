#ifndef WRITERTEST_H
#define WRITERTEST_H

#include <QObject>
#include <QTest>

#include "common/include/writer.h"

class WriterTest : public QObject
{
    Q_OBJECT
public:
    WriterTest();
    enum{HEAD_DATA_SIZE=8};
private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    void testWriteAll();

private:
    Writer * m_writer;
};

#endif // WRITERTEST_H
