#include <QThread>
#include "include/publishrannable.h"

PublishRannable::PublishRannable(const SettingsVO & svo, MainWindow * mw):
    QRunnable()
  , m_svo(svo)
  , m_publish(NULL)
  , m_mainWindow(mw)
{
}

PublishRannable::~PublishRannable()
{
    if (NULL != m_publish)
    {
        delete m_publish;
    }
}

void PublishRannable::run()
{
    m_publish = new Publisher(m_svo);
    m_publish->publish();
    while(m_publish->isFinished() == false)
    {
        if (NULL != m_mainWindow)
        {
            m_mainWindow->updatePublishInfo("1234456778");
        }
        printf("123455678888\n");
        QThread::usleep(500);
    }

    if (NULL != m_mainWindow)
    {
        m_mainWindow->enablePublishBtn();
    }
}
