#include <QTime>
#include <QFile>
#include <QtCore>

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
    chopExcludePath();
    filterMinSizeFile();
    loadCacheData();

    m_fileCount = m_fileLists.size();
    m_succFileLists.clear();
    m_failFileLists.clear();
    m_outInfoLists.clear();
    m_isFinished = false;

    QTime t;
    t.start();

    m_works.setPublisher(this);
    m_works.setInputPath(m_svo.getAbsoluteInputDirPath());
    m_works.setOutputPath(m_svo.getAbsoluteOutputDirPath());
    m_works.start();

    m_works.wait();

    int time = t.elapsed();
    int hour = time / 1000 / 3600;
    int min = (time - hour*1000 * 3600) / 1000 /60 ;
    int sec = (time - hour*1000 * 3600 - min*1000*60) / 1000;
    int ms = time - hour*1000 * 3600 - min*1000*60 - sec * 1000;
    printf("----------cost time: %d hours %d minutes %d seconds %d ms----------\n", hour, min, sec, ms);
    m_isFinished = true;

    m_png2BipCache.save(FileUtils::getPng2BipCacheFilePath(m_svo.getAbsoluteInputDirPath(), m_svo.getFormat()));
    return true;
}

QString Publisher::fetchTask()
{
    QString result = "";
    if (m_fileLists.size() > 0)
    {
        result = *(m_fileLists.begin());
        m_fileLists.pop_front();
    }

    return result;
}

QString Publisher::fetchOutInfo()
{
    QString result = "";
    while (m_outInfoLists.size() > 0)
    {
        if (result.length() > 0)
        {
            result +="\n";
        }

        result += *(m_outInfoLists.begin());
        m_outInfoLists.pop_front();
    }
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

void Publisher::doneFile(bool isSucc, const QString &filePath, const QString & bipFilePath, int width, int height)
{
    QString path = filePath.right(filePath.length() - 1 - m_svo.getAbsoluteInputDirPath().length());
    QString info = path + " ... ... ";

    if (isSucc)
    {
        m_succFileLists.push_back(filePath);
        info +="succ";

        QString bipFullPath = FileUtils::getAbsoluteFilePath(bipFilePath);
        QString bipMd5String = FileUtils::md5File(bipFullPath);
        QString bipPath = bipFullPath.right(bipFullPath.length() - 1 - m_svo.getAbsoluteOutputDirPath().length());

        Png2BipCahceVO p2bvo;
        p2bvo.setPngFilePath(path);

        p2bvo.setPngFileMd5String(FileUtils::md5File(filePath));
        p2bvo.setBipFilePath(bipPath);
        p2bvo.setBipFileMd5String(bipMd5String);

        QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(m_svo.getAbsoluteInputDirPath(), m_svo.getFormat());

        QString bipCacheFullPath = cacheDirPath + "/" + getMd5Path(bipMd5String) + "/" + bipMd5String;
        FileUtils::createParentDirectory(bipCacheFullPath);
        if (FileUtils::copyFile(bipFullPath, bipCacheFullPath))
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
    sprintf(percent, " ... ... %d:%d ... ... %d / %d ... ... %.2f %%", width, height, size, m_fileCount, 1.0f * 100 * size / m_fileCount);

    info += percent;
    m_outInfoLists.push_back(info);

    if (Config::isConsole())
    {
        printf("%s\n", info.toStdString().c_str());
    }
}

void Publisher::loadCacheData()
{
    QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(m_svo.getAbsoluteInputDirPath(), m_svo.getFormat());
    m_png2BipCache.load(FileUtils::getPng2BipCacheFilePath(m_svo.getAbsoluteInputDirPath(), m_svo.getFormat()));
    QVector<QString>::iterator iterator = m_fileLists.begin();
    int inputLen = m_svo.getAbsoluteInputDirPath().length();

    QVector<QString> needRemoveFiles;
    for(; iterator != m_fileLists.end(); iterator++)
    {
        QString md5String = FileUtils::md5File(*iterator);
        QString path =  iterator->right(iterator->length() - inputLen - 1);
        const Png2BipCahceVO * p2bvo = m_png2BipCache.getCacheVO(path, md5String);

        if ((p2bvo != NULL) && (p2bvo->pngFileMd5String() == md5String))
        {
            QString bipCachePath = cacheDirPath + "/" + getMd5Path(p2bvo->bipFileMd5String()) + "/" + p2bvo->bipFileMd5String();
            if (FileUtils::isFile(bipCachePath))
            {
                QString bipFullPath = m_svo.getOutputPath() + "/" + p2bvo->bipFilePath();
                FileUtils::createParentDirectory(bipFullPath);
                FileUtils::copyFile(bipCachePath, bipFullPath);
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

void Publisher::chopExcludePath()
{
    QVector<QString> result;
    QVector<QString>::iterator iterator = m_fileLists.begin();

    for(; iterator != m_fileLists.end(); iterator++)
    {
        if (!m_svo.isInExcludePath(*iterator))
        {
            result.push_back(*iterator);
        }
    }

    m_fileLists = result;
}

void Publisher::filterMinSizeFile()
{
    if (m_svo.minSize() > 0)
    {
        QVector<QString> result;
        QVector<QString>::iterator iterator = m_fileLists.begin();

        for(; iterator != m_fileLists.end(); iterator++)
        {
            if (FileUtils::getFileSize(*iterator) > m_svo.minSize())
            {
                result.push_back(*iterator);
            }
        }

        m_fileLists = result;
    }
}

QString Publisher::getMd5Path(const QString &md5String)
{
    if (md5String.length() > 2)
    {
        return md5String.left(2);
    }

    return "";
}
