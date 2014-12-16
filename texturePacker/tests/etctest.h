#ifndef ETCTEST_H
#define ETCTEST_H

#include <QObject>
#include <QTest>
#include <QString>

class ETCTest : public QObject
{
    Q_OBJECT
public:
    explicit ETCTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testLoadFile();
    void testLoadData();
    void testSave();

private:
    QString m_etcFilePath;
    QString m_etcCCZFilePath;
    QString m_outFilePath;
    QString m_outCCZFilePath;
};

#endif // ETCTEST_H
