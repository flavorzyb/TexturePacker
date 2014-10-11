#include "include/tpapplication.h"
#include "common/include/publisher.h"
#include "common/include/fileutils.h"

bool isConsole(int argc, char *argv[]);

int runInConsole(int argc, char *argv[]);

void print_usage();

int main(int argc, char *argv[])
{

    QString param;
    for (int i = 0; i < argc; ++i)
    {
        param = argv[i];
        param += "\n";
    }

    param += "\n\n";
    FileUtils::writeFile("/Users/flavor/tmp/tp.dat", "ab+", param.toStdString().c_str(), param.length());

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

    if (argc < 8)
    {
        print_usage();
        return 0;
    }

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
    }

    if ((svo.getInputPath().length() < 1) || (svo.getOutputPath().length() < 1))
    {
        print_usage();
        return 0;
    }

    Publisher pub(svo);
    pub.publish();

    return 0;
}
void print_usage()
{
    printf("error: error arguments\n");
    printf("usage: texturePacker -no-gui -i /usr/local/input -o /usr/local/tmp/output -f ios \n");
    printf("       -no-gui run application in console mode \n");
    printf("       -i input directory path \n");
    printf("       -o output directory path \n");
    printf("       -f ios or android\n");
}
