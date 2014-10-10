#include "include/publishthread.h"
#include "common/include/publisher.h"

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


PublishThread::PublishThread():QThread()
{
}

SettingsVO PublishThread::getSettingsVO() const
{
    return m_svo;
}

void PublishThread::setSettingsVO(const SettingsVO &svo)
{
    m_svo = svo;
}

void PublishThread::run()
{
    Publisher publish(m_svo);

    PubThread pb(&publish);
    pb.start();

    while((publish.isFinished() == false) || (pb.isFinished() == false))
    {
        update(publish.fetchOutInfo());
        QThread::usleep(500);
    }

    update(publish.fetchOutInfo());
}
