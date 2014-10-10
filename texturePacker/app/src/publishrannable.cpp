#include <QThread>
#include "include/publishrannable.h"

class PubThread : public QThread
{
public:
    explicit PubThread(Publisher * pub);

private:
    void run();

private:
    Publisher * m_pub;
};

PubThread::PubThread(Publisher *pub):
    QThread()
  , m_pub(pub)
{

}

void PubThread::run()
{
    if (NULL != m_pub)
    {
        m_pub->publish();
    }
}

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
    PubThread pb(m_publish);
    pb.start();

    while(m_publish->isFinished() == false)
    {
        if (NULL != m_mainWindow)
        {
            m_mainWindow->updatePublishInfo("1234456778");
        }
        QThread::usleep(500);
    }

    if (NULL != m_mainWindow)
    {
        m_mainWindow->enablePublishBtn();
    }
}
