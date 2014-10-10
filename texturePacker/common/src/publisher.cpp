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
    m_fileCount = m_fileLists.size();
    m_succFileLists.clear();
    m_failFileLists.clear();
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

#ifdef TP_CMD_MODE
    unsigned int size = m_succFileLists.size() + m_failFileLists.size();
    QString path = filePath.right(filePath.length() - 1 - m_svo.getAbsoluteInputFilePath().length());
    printf("publishing %s ... ... %s ... ... %d / %d ... ... %.2f%%\n", path.toStdString().c_str(), isSucc ? "succ" : "fail", size, m_fileCount, 1.0f * 100 * size / m_fileCount);
#endif
    m_doneMutex.unlock();
}
