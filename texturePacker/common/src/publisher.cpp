#include <QTime>
#include <QFile>

#include "include/publisher.h"
#include "include/fileutils.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/worker.h"
#include "include/config.h"

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
    loadCacheData();

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

    m_png2BipCache.save(FileUtils::getPng2BipCacheFilePath(m_svo.getAbsoluteInputFilePath(), m_svo.getFormat()));
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

void Publisher::doneFile(bool isSucc, const QString &filePath, const QString & bipFilePath)
{
    m_doneMutex.lock();
    QString path = filePath.right(filePath.length() - 1 - m_svo.getAbsoluteInputFilePath().length());
    QString info = path + " ... ... ";

    if (isSucc)
    {
        m_succFileLists.push_back(filePath);
        info +="succ";

        QString bipFullPath = FileUtils::getAbsoluteFilePath(bipFilePath);
        QString bipMd5String = FileUtils::md5File(bipFullPath);
        QString bipPath = bipFullPath.right(bipFullPath.length() - 1 - m_svo.getAbsoluteOutputFilePath().length());

        Png2BipCahceVO p2bvo;
        p2bvo.setPngFilePath(path);
        p2bvo.setPngFileMd5String(FileUtils::md5File(filePath));
        p2bvo.setBipFilePath(bipPath);
        p2bvo.setBipFileMd5String(bipMd5String);

        QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(m_svo.getAbsoluteInputFilePath(), m_svo.getFormat());

        QString bipCacheFullPath = cacheDirPath + "/" + bipPath;
        FileUtils::createParentDirectory(bipCacheFullPath);
        if (QFile::copy(bipFullPath, bipCacheFullPath))
        {
            m_png2BipCache.add(p2bvo);
        }
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

    if (Config::isConsole())
    {
        printf("%s\n", info.toStdString().c_str());
    }

    m_doneMutex.unlock();
}

void Publisher::loadCacheData()
{
    QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(m_svo.getAbsoluteInputFilePath(), m_svo.getFormat());
    m_png2BipCache.load(FileUtils::getPng2BipCacheFilePath(m_svo.getAbsoluteInputFilePath(), m_svo.getFormat()));
    QVector<QString>::iterator iterator = m_fileLists.begin();
    int inputLen = m_svo.getAbsoluteInputFilePath().length();

    QVector<QString> needRemoveFiles;
    for(; iterator != m_fileLists.end(); iterator++)
    {
        QString md5String = FileUtils::md5File(*iterator);
        QString path =  iterator->right(iterator->length() - inputLen - 1);
        const Png2BipCahceVO * p2bvo = m_png2BipCache.getCacheVO(path);
        if ((p2bvo != NULL) && (p2bvo->pngFileMd5String() == md5String))
        {
            QString bipCachePath = cacheDirPath + "/" + p2bvo->bipFilePath();
            QString bipFileMd5String = FileUtils::md5File(bipCachePath);
            if (bipFileMd5String == p2bvo->bipFileMd5String())
            {
                QString bipFullPath = m_svo.getOutputPath() + "/" + p2bvo->bipFilePath();
                FileUtils::createParentDirectory(bipFullPath);
                QFile::copy(bipCachePath, bipFullPath);
                needRemoveFiles.push_back(*iterator);
            }
        }
    }

    //移除已经缓存过的材质
    iterator = needRemoveFiles.begin();
    for(; iterator != needRemoveFiles.end(); iterator++)
    {
        QVector<QString>::iterator findIterator = m_fileLists.begin();
        for (;findIterator != m_fileLists.end(); findIterator++)
        {
            if ((*findIterator) == (*iterator))
            {
                m_fileLists.erase(findIterator);
                break;
            }
        }
    }
}
