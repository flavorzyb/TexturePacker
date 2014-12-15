#include <QTest>

#include "publishertest.h"
#include "common/include/publisher.h"

PublisherTest::PublisherTest(QObject *parent) :
    QObject(parent)
{
}

void PublisherTest::init()
{
    m_svo.setInputPath("input");
    m_svo.setOutputPath("output");
}

void PublisherTest::cleanup()
{
}

void PublisherTest::testGetSettingsVO()
{
    m_svo.setFormat(SettingsVO::IOS);
    Publisher pub(m_svo);
    QCOMPARE(pub.getSettingsVO(), m_svo);
}

void PublisherTest::testPublishIOS()
{
    m_svo.setFormat(SettingsVO::IOS);
    Publisher pub(m_svo);
    QCOMPARE(pub.publish(), true);
}

void PublisherTest::testPublishAndroid()
{
    m_svo.setFormat(SettingsVO::ANDROID);
    Publisher pub(m_svo);
    QCOMPARE(pub.publish(), true);
}
