#ifndef PNG2BIPCACHETEST_H
#define PNG2BIPCACHETEST_H

#include <QObject>
#include <QTest>

#include "common/include/png2bipcache.h"

class Png2BipCacheTest : public QObject
{
    Q_OBJECT
public:
    Png2BipCacheTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testLoad();
    void testSave();

private:
    Png2BipCache * m_cache;
};

#endif // PNG2BIPCACHETEST_H
