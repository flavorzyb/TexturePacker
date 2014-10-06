#ifndef IMAGETEST_H
#define IMAGETEST_H

#include <QObject>
#include <QTest>

#include "common/include/image.h"

class ImageTest : public QObject
{
    Q_OBJECT
public:
    explicit ImageTest();

signals:

public slots:

private Q_SLOTS:
    virtual void init() = 0;
    virtual void cleanup() = 0;
    virtual void testLoad() = 0;
    virtual void testSave() = 0;
    void testWidthAndHeight();

protected:
    Image * m_pImg;
};

#endif // IMAGETEST_H
