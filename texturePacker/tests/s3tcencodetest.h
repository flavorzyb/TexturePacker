#ifndef S3TCENCODETEST_H
#define S3TCENCODETEST_H

#include <QTest>
#include <QString>
#include <QObject>

class S3TCEncodeTest : public QObject
{
    Q_OBJECT
public:
    explicit S3TCEncodeTest();
    virtual ~S3TCEncodeTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConvert();

private:
    QString m_pngPath;
};

#endif // S3TCENCODETEST_H
