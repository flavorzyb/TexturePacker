#include <QFile>
#include <QDir>
#include "include/tpconsoleapplication.h"
#include "common/include/fileutils.h"
#include "common/include/config.h"

ConsolePubThread::ConsolePubThread(const SettingsVO &svo)
{
    m_pub = new Publisher(svo);
}

ConsolePubThread::~ConsolePubThread()
{
    delete m_pub;
}

void ConsolePubThread::run()
{
    m_pub->publish();
}

TPConsoleApplication::TPConsoleApplication(int &argc, char **argv):
    QCoreApplication(argc, argv)
  , m_args(argc)
  , m_isInitCache(false)
  , m_pub(NULL)
{
    Config::setIsConsole(true);

    for (int i = 1; i < argc - 1; ++i)
    {
        if (strcmp("-i", argv[i])==0)
        {
            m_svo.setInputPath(argv[i+1]);
        }
        else if (strcmp("-o", argv[i])==0)
        {
            m_svo.setOutputPath(argv[i+1]);
        }
        else if (strcmp("-f", argv[i])==0)
        {
            if (strcmp("ios", argv[i+1]) == 0)
            {
                m_svo.setFormat(SettingsVO::IOS);
            }
            else if (strcmp("android", argv[i+1]) == 0)
            {
                m_svo.setFormat(SettingsVO::ANDROID);
            }
        }
        else if (strcmp("-init", argv[i])==0)
        {
            m_isInitCache = true;
            m_initCachePath = argv[i+1];
        }
        else if (strcmp("-exclude", argv[i])==0)
        {
            QString excludePathArgv = argv[i+1];
            QStringList excludePathList = excludePathArgv.split(",");
            int size = excludePathList.size();
            for(int i = 0; i < size; i++)
            {
                QString path = excludePathList.at(i).trimmed();
                if (path.length() > 0)
                {
                    m_svo.addExcludePath(path);
                }
            }
        }
    }
}

TPConsoleApplication::~TPConsoleApplication()
{
    if (NULL != m_pub)
    {
        disconnect(m_pub, SIGNAL(finished()), 0, 0);
        delete m_pub;
    }
}

bool TPConsoleApplication::checkConsole()
{
    if (m_args < 8)
    {
        print_usage();
        return false;
    }

    if ((m_svo.getInputPath().length() < 1) || (m_svo.getOutputPath().length() < 1))
    {
        print_usage();
        return false;
    }

    return true;
}

bool TPConsoleApplication::initCache()
{
    if (m_isInitCache && m_initCachePath.length() > 0)
    {
        if (!FileUtils::isDir(m_initCachePath))
        {
            print_usage();
            return false;
        }

        return initCache(m_svo, m_initCachePath);
    }

    return false;
}

void TPConsoleApplication::runConsole()
{
    if (NULL != m_pub)
    {
        disconnect(m_pub, SIGNAL(finished()), 0, 0);
        delete m_pub;
    }

    m_pub = new ConsolePubThread(m_svo);
    connect(m_pub, SIGNAL(finished()), this, SLOT(quit()));
    m_pub->start();
}

void TPConsoleApplication::print_usage()
{
    printf("error: error arguments\n");
    printf("usage: texturePacker -no-gui -i /usr/local/input -o /usr/local/tmp/output -f ios [-init /usr/local/cache] [-exclude /usr/local/input/aaa,/usr/local/input/bbb]\n");
    printf("       -no-gui run application in console mode \n");
    printf("       -i input directory path \n");
    printf("       -o output directory path \n");
    printf("       -f ios or android\n");
    printf("       -init setting init cache dir\n");
    printf("       -exclude exclude path, split by \",\"\n");
}

bool TPConsoleApplication::initCache(const SettingsVO & svo, const QString & initCachePath)
{
    QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(svo.getAbsoluteInputDirPath(), svo.getFormat());
    QString initCacheAbsolutePath = FileUtils::getAbsoluteDirPath(initCachePath);
    unsigned int cachePathLen = initCacheAbsolutePath.length();
    QVector<QString> fileLists = FileUtils::getAllFiles(initCacheAbsolutePath);
    QVector<QString>::iterator iterator = fileLists.begin();

    for(;iterator != fileLists.end(); iterator++)
    {
        QString path = iterator->right(iterator->length() - 1 - cachePathLen);
        QString fullPath = cacheDirPath + "/" + path;
        FileUtils::createParentDirectory(fullPath);
        QFile::copy(*iterator, fullPath);
    }

    return true;
}
