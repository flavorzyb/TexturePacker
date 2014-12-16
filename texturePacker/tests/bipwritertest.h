#ifndef BIPWRITERTEST_H
#define BIPWRITERTEST_H

#include <QObject>
#include <QTest>

#include "common/include/bipwriter.h"

class BipWriterTest : public QObject
{
    Q_OBJECT
public:
    explicit BipWriterTest();

private Q_SLOTS:
    virtual void init();
    virtual void cleanup();
    void testSavePVR();
    void testSaveETC();
};

#endif // BIPWRITERTEST_H
