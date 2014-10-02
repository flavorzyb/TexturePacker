#ifndef PUBLISHERTEST_H
#define PUBLISHERTEST_H

#include <QObject>

#include "common/include/settingsvo.h"

class PublisherTest : public QObject
{
    Q_OBJECT
public:
    explicit PublisherTest(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testGetSettingsVO();
    void testPublish();
private:
    SettingsVO m_svo;
};

#endif // PUBLISHERTEST_H
