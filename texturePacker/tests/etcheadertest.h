#ifndef ETCHEADERTEST_H
#define ETCHEADERTEST_H

#include <QObject>
#include <QTest>
#include <QString>

class ETCHeaderTest : public QObject
{
    Q_OBJECT
public:
    explicit ETCHeaderTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testLoadETCHeader();

private:
    QString m_etcFilePath;
};

#endif // ETCHEADERTEST_H
