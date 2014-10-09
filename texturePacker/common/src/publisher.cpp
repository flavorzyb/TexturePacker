#include <QTime>
#include "include/publisher.h"
#include "include/fileutils.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/worker.h"


Publisher::Publisher(const SettingsVO & svo) :
    QObject(NULL),
    m_svo(svo)
{
}

const SettingsVO & Publisher::getSettingsVO() const
{
    return m_svo;
}

bool Publisher::publish()
{
    m_fileLists = FileUtils::getAllImageFiles(m_svo.getInputPath());
//    QTime t;
//    t.start();
    for (int i = 0; i < MAX_THREAD_NUM; ++i)
    {
        m_works[i].setPublisher(this);
        m_works[i].setInputPath(m_svo.getAbsoluteInputFilePath());
        m_works[i].setOutputPath(m_svo.getOutputPath());
        m_works[i].start();
    }

    for (int i = 0; i < MAX_THREAD_NUM; ++i)
    {
        m_works[i].wait();
    }

//    printf("----------time: %d ms----------\n", t.elapsed());
    return true;
}

QString Publisher::fetchTask()
{
    QString result = "";
    m_mutex.lock();
    if (m_fileLists.size() > 0)
    {
        result = *(m_fileLists.begin());
        m_fileLists.pop_front();
    }
    m_mutex.unlock();

    return result;
}
QVector<QString> Publisher::succFileLists() const
{
    return m_succFileLists;
}

QVector<QString> Publisher::failFileLists() const
{
    return m_failFileLists;
}

void Publisher::doneFile(bool isSucc, const QString &filePath)
{
    m_doneMutex.lock();
    if (isSucc)
    {
        m_succFileLists.push_back(filePath);
    }
    else
    {
        m_failFileLists.push_back(filePath);
    }
    m_doneMutex.unlock();
}
