#ifndef PVRABSTRACTTEST_H
#define PVRABSTRACTTEST_H

#include <QObject>
#include <QTest>

#include "common/include/pvrabstract.h"

class PVRAbstractTest : public QObject
{
    Q_OBJECT
public:
    PVRAbstractTest();
    virtual ~PVRAbstractTest();

protected slots:
    virtual void initTestCase() = 0;
    virtual void cleanupTestCase() = 0;

    void testWidth();
    void testHeight();

signals:

public slots:

protected:
    PVRAbstract * m_oPVR;
};

#endif // PVRABSTRACTTEST_H
