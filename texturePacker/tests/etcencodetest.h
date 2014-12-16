#ifndef ETCENCODETEST_H
#define ETCENCODETEST_H

#include <QObject>
#include <QTest>
#include <QString>

class ETCEncodeTest : public QObject
{
    Q_OBJECT
public:
    ETCEncodeTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConvert();

private:
    QString m_pngPath;
};

#endif // ETCENCODETEST_H
