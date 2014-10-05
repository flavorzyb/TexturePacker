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
    m_svo.setFormat(SettingsVO::IOS);
}

void PublisherTest::cleanup()
{
}

void PublisherTest::testGetSettingsVO()
{
    Publisher pub(m_svo);
    QCOMPARE(pub.getSettingsVO(), m_svo);
}

void PublisherTest::testPublish()
{
    Publisher pub(m_svo);
    QCOMPARE(pub.publish(), true);
}
