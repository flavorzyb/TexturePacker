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
    void init();
    void cleanup();
    void testGetSettingsVO();
    void testPublishIOS();
    void testPublishAndroid();
private:
    SettingsVO m_svo;
};

#endif // PUBLISHERTEST_H
