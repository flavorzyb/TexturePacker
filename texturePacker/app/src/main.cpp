#include "include/tpapplication.h"
#include "include/tpconsoleapplication.h"
#include "common/include/publisher.h"
#include "common/include/fileutils.h"
#include "common/include/config.h"

bool isConsole(int argc, char *argv[]);
void initPathEnv(QCoreApplication *app);

int main(int argc, char *argv[])
{
    if (isConsole(argc, argv))
    {
        TPConsoleApplication ta(argc, argv);
        initPathEnv(&ta);
        if (false==ta.checkConsole())
        {
            return 0;
        }

        if (ta.isInitCache())
        {
            return ta.initCache();
        }

        ta.runConsole();

        return ta.exec();
    }
    else
    {
        TpApplication ta(argc, argv);
        initPathEnv(&ta);
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

void initPathEnv(QCoreApplication *app)
{
    QString path = getenv("PATH");
    path += ":" + app->applicationDirPath();
    setenv("PATH", path.toStdString().c_str(), 1);
}
