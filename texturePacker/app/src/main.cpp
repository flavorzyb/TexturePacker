#include "include/tpapplication.h"
#include "common/include/publisher.h"
#include "common/include/fileutils.h"
#include "common/include/config.h"

bool isConsole(int argc, char *argv[]);

int runInConsole(int argc, char *argv[]);

void initCache(const SettingsVO & svo, const QString & initCachePath);

void print_usage();

int main(int argc, char *argv[])
{
    if (isConsole(argc, argv))
    {
        return runInConsole(argc, argv);
    }
    else
    {
        TpApplication ta(argc, argv);

        ta.initMainWindow();

        return ta.exec();
    }
}

bool isConsole(int argc, char *argv[])
{
    for(int i = 0; i<argc; i++)
    {
        QString param = argv[i];

        if (param.toLower() == "-no-gui")
        {
            return true;
        }
    }

    return false;
}

int runInConsole(int argc, char *argv[])
{
    SettingsVO svo;
    Config::setIsConsole(true);

    if (argc < 8)
    {
        print_usage();
        return 0;
    }

    QString cachePath = "";

    for (int i = 1; i < argc - 1; ++i)
    {
        if (strcmp("-i", argv[i])==0)
        {
            svo.setInputPath(argv[i+1]);
        }
        else if (strcmp("-o", argv[i])==0)
        {
            svo.setOutputPath(argv[i+1]);
        }
        else if (strcmp("-f", argv[i])==0)
        {
            if (strcmp("ios", argv[i+1]) == 0)
            {
                svo.setFormat(SettingsVO::IOS);
            }
            else if (strcmp("android", argv[i+1]) == 0)
            {
                svo.setFormat(SettingsVO::ANDROID);
            }
        }
        else if (strcmp("-init", argv[i])==0)
        {
            cachePath = argv[i+1];
        }
    }

    if ((svo.getInputPath().length() < 1) || (svo.getOutputPath().length() < 1))
    {
        print_usage();
        return 0;
    }

    if (cachePath.length() > 0)
    {
        if (!FileUtils::isDir(cachePath))
        {
            print_usage();
            return 0;
        }

        initCache(svo, cachePath);
        return 0;
    }

    Publisher pub(svo);
    pub.publish();

    return 0;
}
void print_usage()
{
    printf("error: error arguments\n");
    printf("usage: texturePacker -no-gui -i /usr/local/input -o /usr/local/tmp/output -f ios [-init /usr/local/cache]\n");
    printf("       -no-gui run application in console mode \n");
    printf("       -i input directory path \n");
    printf("       -o output directory path \n");
    printf("       -f ios or android\n");
    printf("       -init setting init cache dir\n");
}

void initCache(const SettingsVO & svo, const QString & initCachePath)
{
    QString cacheDirPath = FileUtils::getPng2BipCacheDirPath(svo.getAbsoluteInputFilePath(), svo.getFormat());
    QString initCacheAbsolutePath = FileUtils::getAbsoluteFilePath(initCachePath);
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
}
