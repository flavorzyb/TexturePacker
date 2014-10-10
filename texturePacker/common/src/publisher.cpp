#include <QTime>
#include "include/publisher.h"
#include "include/fileutils.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/worker.h"


Publisher::Publisher(const SettingsVO & svo) :
    QObject(NULL)
  , m_svo(svo)
  , m_isFinished(false)
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
    m_outInfoLists.clear();
    m_isFinished = false;
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
    m_isFinished = true;
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

QString Publisher::fetchOutInfo()
{
    QString result = "";
    m_doneMutex.lock();
    while (m_outInfoLists.size() > 0)
    {
        if (result.length() > 0)
        {
            result +="\n";
        }

        result += *(m_outInfoLists.begin());
        m_outInfoLists.pop_front();
    }
    m_doneMutex.unlock();
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
    QString path = filePath.right(filePath.length() - 1 - m_svo.getAbsoluteInputFilePath().length());
    QString info = path + " ... ... ";

    if (isSucc)
    {
        m_succFileLists.push_back(filePath);
        info +="succ";
    }
    else
    {
        m_failFileLists.push_back(filePath);
        info +="fail";
    }

    char percent[1024] = {0};
    unsigned int size = m_succFileLists.size() + m_failFileLists.size();
    sprintf(percent, " ... ... %d / %d ... ... %.2f %%", size, m_fileCount, 1.0f * 100 * size / m_fileCount);

    info += percent;
    m_outInfoLists.push_back(info);

#ifdef TP_CMD_MODE
    printf("%s\n", info.toStdString().c_str());
#endif
    m_doneMutex.unlock();
}
