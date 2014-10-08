#ifndef READERTEST_H
#define READERTEST_H

#include <QObject>
#include "common/include/reader.h"

class ReaderTest : public QObject
{
    Q_OBJECT
public:
    ReaderTest();

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
